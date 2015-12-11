#include "vibraplotter.h"
#include <fftw3.h>
#include <qtablewidget.h>
#include <qmessagebox.h>
#include <ctime>
#include <QProgressDialog>
#include <QThread>
#include <QProgressBar>

#define PI 3.1416
#define N 52734

const int samples_per_second = 52734;
const int bytes_per_sample = 3;
const int number_of_channels = 7;

VibraPlotter::VibraPlotter(QWidget *parent) : QMainWindow(parent)
{
	//Create Gui variable
	gui = new Ui_VibraPlotterClass();
	gui->setupUi(this);

	//Initialize load variable
	dataLoaded = false;

	//Initialize current index channel
	curr_ch_idx = 1;

	//Initialize number of channels
	Nchannels = 5;

	//Initialize comments vector
	Comments.resize(5);

	//Initialize project opened
	projOpened = false;

	//Create projects directory
	mainSavePath = "D:/QT projects/vs/VibraPlotter/VibraPlotter/SavedProjects";
	if (!QDir().exists(mainSavePath))
	{
		QDir().mkdir(mainSavePath);
	}

	//------------------------------------
	//New Project Dialog

	//Create NewProject Dialog
	newProject = new QDialog(this);
	ui_newProject = new Ui_Dialog();
	ui_newProject->setupUi(newProject);

	//Show new project dialog when clicked
	connect(gui->actionNewProject, SIGNAL(triggered()), this, SLOT(ShowNewProjectDialog()));
	
	//Update and show sensitivity table
	connect(ui_newProject->channels_cbox, SIGNAL(currentIndexChanged(int)), this, SLOT(UpdateTable_new()));

	//Validate and accept new project
	connect(ui_newProject->AcceptNewButton, SIGNAL(clicked()), this, SLOT(ValidateAccept_newProj()));

	//Cancel new project
	connect(ui_newProject->CancelNewButton, SIGNAL(clicked()), this, SLOT(Cancel_NewProj()));
	//------------------------------------

	//------------------------------------
	//Load Project Dialog

	//Create loadProject Dialog
	loadProject = new QDialog(this);
	ui_loadProject = new Ui_loadProject();
	ui_loadProject->setupUi(loadProject);

	//Show load project dialog when clicked
	connect(gui->actionLoadProject, SIGNAL(triggered()), this, SLOT(ShowLoadProjectDialog()));

	//Accept load project
	connect(ui_loadProject->AcceptLoadButton, SIGNAL(clicked()), this, SLOT(Accept_LoadProj()));

	//Cancel load project
	connect(ui_loadProject->CancelLoadButton, SIGNAL(clicked()), this, SLOT(Cancel_LoadProj()));
	//------------------------------------

	//------------------------------------
	//Save Project Dialog

	//Initially set disabled save dialog
	gui->actionSaveProject->setEnabled(false);

	//Create loadProject Dialog
	saveProject = new QDialog(this);
	ui_saveProject = new Ui_saveProject();
	ui_saveProject->setupUi(saveProject);

	//Show save project dialog when icon clicked
	connect(gui->actionSaveProject, SIGNAL(triggered()), this, SLOT(ShowSaveProjectDialog()));

	//Accept and save new project
	connect(ui_saveProject->AcceptSaveButton, SIGNAL(clicked()), this, SLOT(AcceptSave()));

	//Cancel save project
	connect(ui_saveProject->CancelSaveButton, SIGNAL(clicked()), this, SLOT(Cancel_SaveProj()));
	//------------------------------------

	//------------------------------------
	//Settings Dialog

	//Initially set disabled save dialog
	gui->actionSettings->setEnabled(false);

	//Create loadProject Dialog
	settings = new QDialog(this);
	ui_settings = new Ui_settings();
	ui_settings->setupUi(settings);

	//Show save project dialog when icon clicked
	connect(gui->actionSettings, SIGNAL(triggered()), this, SLOT(ShowSettingsDialog()));

	//Update and show sensitivity table
	connect(ui_settings->channels_cbox, SIGNAL(currentIndexChanged(int)), this, SLOT(UpdateTable_set()));

	//Validate and accept new settings
	connect(ui_settings->acceptSettings_button, SIGNAL(clicked()), this, SLOT(ValidateAccept_setProj()));

	//------------------------------------

	//------------------------------------
	//Communication 

	//Get available serial ports
	ListSerialPorts();

	//Create communication manager object
	serial_manager = new CommunicationManager();

	//Connect to error handle if serial port error
	connect(serial_manager->serial, SIGNAL(error(QSerialPort::SerialPortError)), this, SLOT(handleError(QSerialPort::SerialPortError)));

	//Connect to read data function if serial port is ready to read
	connect(serial_manager->serial, SIGNAL(readyRead()), this, SLOT(readData()));

	//Initialize variables
	adq_status = _NONE;
	packages_made = false;
	channels_to_read = 0;
	packages_to_read = 0;
	current_package = 0;
	reading_packages = false;
	//------------------------------------

	//Load data if push button
	connect(gui->LoadButton, SIGNAL(clicked()), this, SLOT(loadData()));

	//Select to plot a channel 
	connect(gui->channel_combo_box, SIGNAL(currentIndexChanged(int)), this, SLOT(FourierPlot()));

}

VibraPlotter::~VibraPlotter()
{

}

void VibraPlotter::ShowNewProjectDialog()
{
	//Set project name with date and time
	GetDateTime();
	ui_newProject->projectName_edit->setText(DateTime);

	//Set combobox to Nchannels
	ui_newProject->channels_cbox->setCurrentIndex(Nchannels-1);

	//Initialize serial port combobox
	ui_newProject->serialPort_cbox->insertItems(0,portList);
	
	//Initialize sensitivity table
	QTableWidget *SensTable = ui_newProject->tableSensitivity;
	SensTable->setColumnCount(2);
	SensTable->setRowCount(Nchannels);

	QStringList column_names;
	column_names << "Channel Id" << "Sensitivity";
	SensTable->setHorizontalHeaderLabels(column_names);

	for (int i = 0; i < Nchannels + 1; i++)
	{
		QTableWidgetItem * id_channel = new QTableWidgetItem(QString::number(i + 1));
		id_channel->setFlags(Qt::NoItemFlags);
		SensTable->setItem(i, 0, id_channel);

		QTableWidgetItem * sense_channel = new QTableWidgetItem(QString::number(10));
		sense_channel->setFlags(Qt::ItemIsEnabled | Qt::ItemIsEditable);
		SensTable->setItem(i, 1, sense_channel);
	}
	SensTable->verticalHeader()->setVisible(false);
	SensTable->horizontalHeader()->setStretchLastSection(true);

	//Show new project dialog
	newProject->exec();
}

void VibraPlotter::UpdateTable_new()
{
	//Read number of channels 
	Nchannels = ui_newProject->channels_cbox->currentIndex() + 1;

	//Set sensitivity vector
	Sensitivity = QVector<double>(Nchannels, 10);

	//Update sensitivity table
	UpdateSensitivityTable(ui_newProject->tableSensitivity);
}

void VibraPlotter::UpdateSensitivityTable(QTableWidget *SensTable)
{
	//Resize comments size
	Comments.resize(Nchannels);

	//Set sensitivity table accoriding input
	SensTable->setColumnCount(2);
	SensTable->setRowCount(Nchannels);

	QStringList column_names;
	column_names << "Channel Id" << "Sensitivity";
	SensTable->setHorizontalHeaderLabels(column_names);

	for (int i = 0; i < Nchannels; i++)
	{
		QTableWidgetItem * id_channel = new QTableWidgetItem(QString::number(i + 1));
		id_channel->setFlags(Qt::NoItemFlags);
		SensTable->setItem(i, 0, id_channel);

		QTableWidgetItem * sense_channel = new QTableWidgetItem(QString::number(Sensitivity[i]));
		sense_channel->setFlags(Qt::ItemIsEnabled | Qt::ItemIsEditable);
		SensTable->setItem(i, 1, sense_channel);
	}
	SensTable->verticalHeader()->setVisible(false);
	SensTable->horizontalHeader()->setStretchLastSection(true);
}

void VibraPlotter::ValidateAccept_newProj()
{
	//Validate project name
	QString Pname = ui_newProject->projectName_edit->text();

	if (Pname == "")
	{
		QMessageBox errorBox;
		errorBox.setWindowTitle("Error");
		errorBox.setIcon(QMessageBox::Icon::Critical);
		errorBox.setText("Set a project name");
		errorBox.setDefaultButton(QMessageBox::Ok);
		errorBox.exec();
		return;
	}
	if (Pname.indexOf('.') >= 0 || Pname.indexOf('*') >= 0)
	{
		QMessageBox errorBox;
		errorBox.setWindowTitle("Error");
		errorBox.setIcon(QMessageBox::Icon::Critical);
		errorBox.setText("Set a valid project name");
		errorBox.setDefaultButton(QMessageBox::Ok);
		errorBox.exec();
		return;
	}

	//Copy to class variable
	ProjName = Pname;

	//Validate sensitivity values from table
	QTableWidget *SensTable = ui_newProject->tableSensitivity;
	QString Sens, ErrSens, NchSens;

	Sensitivity.clear();

	for (int i = 0; i < Nchannels; i++)
	{
		Sens = SensTable->item(i, 1)->text();

		if (!ValidateNumber(Sens))
		{
			QMessageBox errorBox;
			errorBox.setWindowTitle("Error");
			errorBox.setIcon(QMessageBox::Icon::Critical);
			NchSens = QString::number(i + 1);
			ErrSens = "Set a valid sensitivity value for channel ";
			ErrSens.append(NchSens);
			errorBox.setText(ErrSens);
			errorBox.setDefaultButton(QMessageBox::Ok);
			errorBox.exec();
			return;
		}
		else
		{
			//Copy to class variable
			Sensitivity.append(Sens.toDouble());
		}
	}

	//Copy Recording time to class variables
	Rec_Time = ui_newProject->recTime_sbox->value();

	//Close new project dialog
	newProject->close();

	//Show status bar message
	QString stMessage;
	stMessage = "Project ";
	stMessage.append(Pname);
	stMessage.append(" succesfully created!");
	gui->statusBar->showMessage(stMessage);

	//Change flag
	projOpened = true;

	//Enable save and settings actions
	gui->actionSaveProject->setEnabled(true);
	gui->actionSettings->setEnabled(true);
}

void VibraPlotter::Cancel_NewProj()
{
	//Close new project dialog
	newProject->close();
}

void VibraPlotter::ShowLoadProjectDialog()
{
	//Load saved projects from dir
	LoadSaveProjectsDIR();
	int NsavedPojects = savedProjects.size();

	//Set saved projects table 
	QTableWidget *ProjTable = ui_loadProject->tableProjects;
	ProjTable->setColumnCount(3);
	ProjTable->setRowCount(NsavedPojects);

	QStringList column_names;
	column_names << "Name" << "Channels"<< "Recorded time";
	ProjTable->setHorizontalHeaderLabels(column_names);
	ProjTable->setColumnWidth(0, 200);
	ProjTable->setColumnWidth(1, 70);
	ProjTable->setColumnWidth(2, 95);

	for (int i = 0; i < NsavedPojects; i++)
	{
		//Set project name
		QTableWidgetItem * savedProjName = new QTableWidgetItem(savedProjects[i]);
		savedProjName->setFlags(Qt::ItemIsEnabled | Qt::ItemIsSelectable);
		ProjTable->setItem(i, 0, savedProjName);

		//Load XML to show Number of channels and recording time
		QString XMLpath = mainSavePath + "/" + savedProjects[i]+ "/Info.xml";
		LoadXML(XMLpath, false);

		//Set number of channels
		QTableWidgetItem * savedProjNch = new QTableWidgetItem(QString::number(NChannels_proj));
		savedProjNch->setFlags(Qt::ItemIsEnabled | Qt::ItemIsSelectable);
		ProjTable->setItem(i, 1, savedProjNch);

		//Set recording time
		QTableWidgetItem * savedProjRec = new QTableWidgetItem(QString::number(RecTime_proj));
		savedProjRec->setFlags(Qt::ItemIsEnabled | Qt::ItemIsSelectable);
		ProjTable->setItem(i, 2, savedProjRec);
	}

	ProjTable->setSelectionBehavior(QAbstractItemView::SelectRows);
	ProjTable->setSelectionMode(QAbstractItemView::SingleSelection);
	//QItemSelectionModel *loadSelect = ProjTable->selectionModel();
	ProjTable->selectRow(0);
	
	//Show load project dialog
	loadProject->exec();
}

void VibraPlotter::Accept_LoadProj()
{
	QTableWidget *ProjTable = ui_loadProject->tableProjects;
	int sel_proj = ProjTable->currentIndex().row();

	//Load XML to show Number of channels and recording time
	QString XMLpath = mainSavePath + "/" + savedProjects[sel_proj] + "/Info.xml";
	LoadXML(XMLpath, true);

	//Load project name
	ProjName = savedProjects[sel_proj];

	//Change flag
	projOpened = true;

	//Close load project dialog
	loadProject->close();

	//Enable save and settings actions
	gui->actionSaveProject->setEnabled(true);
	gui->actionSettings->setEnabled(true);

	//Show status bar message
	QString stMessage;
	stMessage = "Project ";
	stMessage.append(savedProjects[sel_proj]);
	stMessage.append(" succesfully loaded!");
	gui->statusBar->showMessage(stMessage);
}

void VibraPlotter::Cancel_LoadProj()
{
	//Close load project dialog
	loadProject->close();
}

void VibraPlotter::LoadSaveProjectsDIR()
{
	//Read saved projects directory
	QDir savedProjs(mainSavePath);
	QStringList savedProjsList = savedProjs.entryList();

	//iterate through saved projects directory
	savedProjects.clear();
	for (int i = 0; i < savedProjsList.size(); i++)
	{
		//avoid system files "." ".."
		if (savedProjsList.at(i).size() > 2)
		{
			savedProjects.append(savedProjsList.at(i).toLocal8Bit().constData());
		}
	}
}

void VibraPlotter::LoadXML(QString XMLfile, bool flag_global_copy)
{
	//Local Variables
	int lcl_Nchannels;
	QString lcl_DateTime;
	QVector<double> lcl_Sensitivity;
	QVector<QString> lcl_Comments;
	int lcl_Rec_Time;

	//Read XML
	QFile xmlFile(XMLfile);
	xmlFile.open(QIODevice::ReadOnly);
	QDomDocument document;
	document.setContent(&xmlFile);
	QDomElement vibraElem = document.firstChildElement();

	//ReadXML info
	QDomElement info = vibraElem.firstChildElement();

	//Get number of channels
	lcl_Nchannels = info.attribute("Channels").toInt();
	NChannels_proj = lcl_Nchannels;

	//Get creation date and time
	lcl_DateTime = info.attribute("Date_time");

	//Get recording time
	lcl_Rec_Time = info.attribute("Recording_time").toInt();
	RecTime_proj = lcl_Rec_Time;

	//Get sensitivity 
	QDomElement sensitivity = vibraElem.firstChildElement("Sensitivity");
	QDomNodeList nodes = sensitivity.elementsByTagName("Sense");
	for (int i = 0; i < nodes.size(); i++)
	{
		QDomNode elm = nodes.at(i);
		if (elm.isElement())
		{
			QDomElement sensch = elm.toElement();
			lcl_Sensitivity.append(sensch.attribute("level").toDouble());
		}
	}

	//Get comments
	QDomElement comments = vibraElem.lastChildElement();
	nodes = comments.elementsByTagName("Comment");
	for (int i = 0; i < nodes.size(); i++)
	{
		QDomNode elm = nodes.at(i);
		if (elm.isElement())
		{
			QDomElement comment = elm.toElement();
			lcl_Comments.append(comment.attribute("level"));
		}
	}

	//If flag, copy to class variables
	if (flag_global_copy)
	{
		Nchannels = lcl_Nchannels;
		DateTime = lcl_DateTime;
		Sensitivity = lcl_Sensitivity;
		Comments = lcl_Comments;
		Rec_Time = lcl_Rec_Time;
	}
}

void VibraPlotter::ShowSaveProjectDialog()
{
	//Set default save name
	ui_saveProject->ProjectNameSaveEdit->setText(ProjName);

	//Set default save .txt file
	ui_saveProject->txtSave->setChecked(true);

	//Show save project dialog
	saveProject->exec();
}

void VibraPlotter::AcceptSave()
{
	ProjName = ui_saveProject->ProjectNameSaveEdit->text();

	//Save current channel comments
	QString curr_Comment = gui->ChannelComments->toPlainText();
	Comments[curr_ch_idx] = curr_Comment;

	//Validate there are comments for channels
	ValidateCommentArray();

	//Create project directory
	projSavePath = mainSavePath + "/" + ProjName;
	QDir().mkdir(projSavePath);

	//Save data.bin file


	//Save XML File
	SaveXML();

	//Close save project dialog
	saveProject->close();
	
	//Show status bar message
	QString stMessage;
	stMessage = "Project ";
	stMessage.append(ProjName);
	stMessage.append(" succesfully saved!");
	gui->statusBar->showMessage(stMessage);
}

void VibraPlotter::Cancel_SaveProj()
{
	//Close save project dialog
	saveProject->close();
}

void VibraPlotter::SaveXML()
{
	//Create XML file and open
	QString ProjFile = projSavePath + "/Info.xml";
	QFile file(ProjFile); 
	file.open(QIODevice::WriteOnly);
	
	//Generate XML structure
	QDomDocument mainXML;
	
	//Main info
	QDomElement vibraElem = mainXML.createElement("VibraPlotter");
	vibraElem.setAttribute("version", "0.8");
	mainXML.appendChild(vibraElem);
	QDomElement info = mainXML.createElement("Info");
	info.setAttribute("Date_time ", DateTime);
	info.setAttribute("Channels ", Nchannels);
	info.setAttribute("Recording_time ", Rec_Time);
	vibraElem.appendChild(info);

	//Sensitivity
	QDomElement sensitivity = mainXML.createElement("Sensitivity");
	vibraElem.appendChild(sensitivity);
	for (int i = 0; i < Nchannels; i++)
	{
		QDomElement sensech = mainXML.createElement("Sense");
		sensech.setAttribute("channel", i + 1);
		sensech.setAttribute("level", Sensitivity[i]);
		sensitivity.appendChild(sensech);
	}

	//Comments
	QDomElement comments = mainXML.createElement("Comments");
	vibraElem.appendChild(comments);
	for (int i = 0; i < Nchannels; i++)
	{
		QDomElement commment = mainXML.createElement("Comment");
		commment.setAttribute("channel", i + 1);
		commment.setAttribute("text", Comments[i]);
		comments.appendChild(commment);
	}

	//Write and close XML
	QTextStream stream(&file);
	stream << mainXML.toString();
	file.close();
}

void VibraPlotter::SaveBinData()
{
	QString saveBinDataPath = projSavePath + "/Data.bin";

}

void VibraPlotter::SaveTxtData()
{
	QString saveTxtDataPath = projSavePath + "/Data.txt";


}

void VibraPlotter::ShowSettingsDialog()
{
	//Set save name
	ui_settings->projectName_edit->setText(ProjName);

	//Set combobox to Nchannels
	ui_settings->channels_cbox->setCurrentIndex(Nchannels - 1);

	//Set serial port combobox
	ui_settings->serialPort_cbox->insertItems(0, portList);

	//Set sensitivity table 
	QTableWidget *SensTable = ui_settings->sensitivity_table;
	SensTable->setColumnCount(2);
	SensTable->setRowCount(Nchannels);

	QStringList column_names;
	column_names << "Channel Id" << "Sensitivity";
	SensTable->setHorizontalHeaderLabels(column_names);

	for (int i = 0; i < Nchannels; i++)
	{
		QTableWidgetItem * id_channel = new QTableWidgetItem(QString::number(i + 1));
		id_channel->setFlags(Qt::NoItemFlags);
		SensTable->setItem(i, 0, id_channel);

		QTableWidgetItem * sense_channel = new QTableWidgetItem(QString::number(Sensitivity[i]));
		sense_channel->setFlags(Qt::ItemIsEnabled | Qt::ItemIsEditable);
		SensTable->setItem(i, 1, sense_channel);
	}
	SensTable->verticalHeader()->setVisible(false);
	SensTable->horizontalHeader()->setStretchLastSection(true);

	//Show settings dialog
	settings->exec();
}

void VibraPlotter::UpdateTable_set()
{
	//Read number of channels 
	Nchannels = ui_settings->channels_cbox->currentIndex() + 1;

	//Update sensitivity size
	Sensitivity.resize(Nchannels);
	
	//Update sensitivity table
	UpdateSensitivityTable(ui_settings->sensitivity_table);
}

void VibraPlotter::ValidateAccept_setProj()
{
	//Validate project name
	QString Pname = ui_settings->projectName_edit->text();

	if (Pname == "")
	{
		QMessageBox errorBox;
		errorBox.setWindowTitle("Error");
		errorBox.setIcon(QMessageBox::Icon::Critical);
		errorBox.setText("Set a project name");
		errorBox.setDefaultButton(QMessageBox::Ok);
		errorBox.exec();
		return;
	}
	if (Pname.indexOf('.') >= 0 || Pname.indexOf(':') >= 0 || Pname.indexOf('*') >= 0)
	{
		QMessageBox errorBox;
		errorBox.setWindowTitle("Error");
		errorBox.setIcon(QMessageBox::Icon::Critical);
		errorBox.setText("Set a valid project name (avoid '.','*',':')");
		errorBox.setDefaultButton(QMessageBox::Ok);
		errorBox.exec();
		return;
	}

	//Copy to class variable
	ProjName = Pname;

	//Validate sensitivity values from table
	QTableWidget *SensTable = ui_settings->sensitivity_table;
	QString Sens, ErrSens, NchSens;

	Sensitivity.clear();

	for (int i = 0; i < Nchannels; i++)
	{
		Sens = SensTable->item(i, 1)->text();

		if (!ValidateNumber(Sens))
		{
			QMessageBox errorBox;
			errorBox.setWindowTitle("Error");
			errorBox.setIcon(QMessageBox::Icon::Critical);
			NchSens = QString::number(i + 1);
			ErrSens = "Set a valid sensitivity value for channel ";
			ErrSens.append(NchSens);
			errorBox.setText(ErrSens);
			errorBox.setDefaultButton(QMessageBox::Ok);
			errorBox.exec();
			return;
		}
		else
		{
			//Copy to class variable
			Sensitivity.append(Sens.toDouble());
		}
	}

	//Copy Recording time to class variables
	Rec_Time = ui_settings->recTime_sbox->value();

	//Close new project dialog
	settings->close();

	//Show status bar message
	QString stMessage;
	stMessage = "Project ";
	stMessage.append(Pname);
	stMessage.append(" succesfully updated!");
	gui->statusBar->showMessage(stMessage);

}

void VibraPlotter::readData()
{
	QByteArray data = serial_manager->serial->readAll();

	serial_manager->data_counter += data.size();


	for (int i = 0; i < data.size(); i++) 
	{
		serial_manager->protocol_frame_analyzer(data.at(i) & 0xFF);
	}

	if (reading_packages) {
		//QApplication::processEvents();

		if (package_progress_dialog->wasCanceled()) {
			package_progress_dialog->close();
		}
		else {
			package_progress_dialog->setValue((current_package - 1)*ADQ_BYTES_PER_SAMPLE*ADQ_SAMPLES_PER_SECOND*channels_to_read + 
				(serial_manager->data_counter > 6 ? serial_manager->data_counter - 6 : 0));
		}
	}

}

void VibraPlotter::ValidateCommentArray()
{
	QString ErrSens, NchSens;

	QMessageBox warnBox;
	warnBox.setWindowTitle("Warning");
	warnBox.setIcon(QMessageBox::Icon::Warning);
	ErrSens = "Do you want to save without any comments for channels: ";

	for (int i = 0; i < Nchannels; i++)
	{
		if (Comments[i].isEmpty())
		{
			NchSens = QString::number(i + 1);
			ErrSens.append(NchSens);
			ErrSens.append(" ");
		}
	}

	warnBox.setText(ErrSens);
	warnBox.setStandardButtons(QMessageBox::Yes | QMessageBox::No);
	warnBox.setDefaultButton(QMessageBox::Yes);
	int sel = warnBox.exec();
}

bool VibraPlotter::ValidateNumber(const QString &Input)
{
	//convert qstring to string
	std::string Instr = Input.toLocal8Bit().constData();

	//iterate through string checking for no numbers
	return !Instr.empty() && std::find_if(Instr.begin(),
		Instr.end(), [](char c) { return !isdigit(c)&&c!='.'; }) == Instr.end();
}

void VibraPlotter::GetDateTime()
{
	time_t rawtime;
	struct tm * timeinfo;
	char buffer[80];

	time(&rawtime);
	timeinfo = localtime(&rawtime);

	strftime(buffer, 80, "%d-%m-%Y_%I-%M-%S", timeinfo);
	QString str(buffer);

	DateTime = str;
}

void VibraPlotter::ListSerialPorts()
{
	QList<QSerialPortInfo> ports = QSerialPortInfo::availablePorts();

	foreach(const QSerialPortInfo &item, ports)
		portList << item.portName();
}

void VibraPlotter::loadData( )
{
	//Read real Data
	ReadBinFile("D:\\QT projects\\Plot_v1\\nov_17_10_26\\senales.bin");
	dataLoaded = true;

	//Create time vector for plotting
	Time_vec.clear();
	for (int i = 0; i < N; i++)
	{
		Time_vec.push_back(double(i) / samples_per_second);
	}

	//Create frequency vector for plotting
	Freq_vec.clear();
	for (int i = 0; i < (N / 2); i++)
	{
		Freq_vec.push_back(double(samples_per_second)*double(i) / N);
	}

	//Calculate Fourier transform for all channels
	QVector<double> Fy;
	for (int i = 0; i < Channels.size(); i++)
	{
		Fy = Fourier_Calc(Channels[i]);
		FChannels.push_back(Fy);
	}

	//Calculate Fourier and Plot first channel
	FourierPlot();
	gui->statusBar->showMessage("Datos cargados!");
}

void VibraPlotter::FourierPlot()
{
	//If data is loaded Plot, else load it
	if (dataLoaded)
	{
		//Save current channel comments
		QString curr_Comment = gui->ChannelComments->toPlainText();
		Comments[curr_ch_idx] = curr_Comment;

		//Get new channel index 
		curr_ch_idx = gui->channel_combo_box->currentIndex();

		//Set new selected channel comment
		gui->ChannelComments->setText(Comments[curr_ch_idx]);

		//Plot data (time)
		Plot(gui->signalPlot, Time_vec, Channels[curr_ch_idx], "Time (s)", "Amplitude");

		//Plot data (frequency)
		Plot(gui->fourierPlot, Freq_vec, FChannels[curr_ch_idx], "Frequency (Hz)", "Amplitude");

		//Set comments label
		QString Chlbl = "Comments for channel ";
		QString Ch = QString::number(curr_ch_idx + 1);
		Chlbl.append(Ch);
		gui->CommentsLbl->setText(Chlbl);
	}
	else
	{
		loadData();
	}
}

//Compute Discrete Fourier Transform from input data
QVector<double> VibraPlotter::Fourier_Calc(QVector<double> In_data)
{
	double *out_fft, *in_fft;
	fftw_plan p;

	//Allocate memory for DFT
	out_fft = (double*)fftw_malloc(sizeof(double) * N);
	in_fft = (double*)fftw_malloc(sizeof(double) * N);
	QVector<double> out_fft1;

	//Set DFT plan (parameters)
	p = fftw_plan_r2r_1d(N, in_fft, out_fft, FFTW_R2HC, FFTW_ESTIMATE);

	//Copy Input data to DFT data vector type
	for (int i = 0; i<In_data.size(); i++)
	{
		in_fft[i] = In_data[i];
	}

	//Execute DFT
	fftw_execute(p);

	//Post-process (square and select positive side)
	for (int i = 1; i < ((N / 2)); i++)
	{
		out_fft1.push_back(out_fft[i] * out_fft[i]);
	}

	return out_fft1;
}

//Plot X against Y vectors in Axes
void VibraPlotter::Plot(QCustomPlot *Axes, QVector<double> X, QVector<double> Y, QString Xlbl, QString Ylbl,
	double Ymin, double Ymax, double Xmin, double Xmax)
{
	// create graph and assign data to it:
	Axes->addGraph();
	Axes->graph(0)->setData(X, Y);
	// give the axes some labels:
	Axes->xAxis->setLabel(Xlbl);
	Axes->yAxis->setLabel(Ylbl);
	// set axes ranges, so we see all data:
	double Xlims, Xlimi;

	if (Xmin == 0)
		Xlimi = X[0];
	else
		Xlimi = Xmin;

	if (Xmax == 0)
		Xlims = X[X.size() - 1];
	else
		Xlims = Xmax;

	Axes->xAxis->setRange(Xlimi, Xlims);

	double Ylims, Ylimi;

	if (Ymin == 0 && Ymax == 0)
	{
		MaxMin_QVector(Y, Ylims, Ylimi);
	}
	else
	{
		Ylimi = Ymin;
		Ylims = Ymax;
	}

	Axes->yAxis->setRange(Ylimi, Ylims);

	//Allow plot zoom and range 
	Axes->setInteraction(QCP::iRangeZoom, true);
	Axes->setInteraction(QCP::iRangeDrag, true);
	Axes->axisRect()->setRangeDrag(Qt::Horizontal);
	Axes->axisRect()->setRangeZoom(Qt::Horizontal);
	Axes->replot();
}

//Find max and min value from QVector
void VibraPlotter::MaxMin_QVector(QVector<double> A, double &maxA, double &minA)
{
	maxA = -1000000;
	minA = 1000000;

	for (int i = 0; i < A.size(); i++)
	{
		if (A[i]>maxA)
			maxA = A[i];
		if (A[i] < minA)
			minA = A[i];
	}
}

//Read bin file and convert to Array
void VibraPlotter::ReadBinFile(QString Path)
{
	std::ifstream infile;
	infile.open(Path.toStdString(), std::ios::binary | std::ios::in);

	QVector<QVector<int>> Total_bytes;

	unsigned char buffer[bytes_per_sample];

	for (int j = 0; j<number_of_channels; j++) {
		//qDebug() << "Processing channel " << j << "\n";
		std::cout << "Processing channel " << j << "\n";
		QVector<int> channel_bytes;
		for (int i = 0; i<samples_per_second; i++) {
			infile.read((char *)&buffer, sizeof(buffer));
			unsigned int value = (buffer[0] << 16) + (buffer[1] << 8) + (buffer[2] << 0);
			channel_bytes.push_back(value);
		}
		Total_bytes.push_back(channel_bytes);
	}

	//Scale Data
	double val_hex_pos_max = 16777216.0;
	double val_volt_max = 5.0;

	for (int j = 0; j<number_of_channels; j++) {
		QVector<double> channel_bytes;
		for (int i = 0; i<samples_per_second; i++) {
			double valor_escalado = (double)(Total_bytes.at(j).at(i)*val_volt_max) / ((double)val_hex_pos_max);

			if (valor_escalado >= 2.5) {
				valor_escalado += -5.0;
			}

			channel_bytes.push_back(valor_escalado);
		}
		Channels.push_back(channel_bytes);
	}
}


void VibraPlotter::startADQ() {
	int numTasks = 100000000;
	QProgressBar * progressBar = new QProgressBar(this);
	progressBar->setRange(0, 0);
	progressBar->setTextVisible(false);

	QProgressDialog progress("Adquiring data...", "Cancel", 0, 0, this);
	progress.setBar(progressBar);
	progress.setWindowModality(Qt::WindowModal);
	progress.open();

	for (int i = 0; i < numTasks; i++) {
		QThread::msleep(10);
		progressBar->setValue(0);
		progress.setValue(0);
		QApplication::processEvents();

		if (progress.wasCanceled())
			break;
	}
	progress.cancel();
}

