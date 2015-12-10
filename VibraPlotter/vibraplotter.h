#ifndef VIBRAPLOTTER_H
#define VIBRAPLOTTER_H

#include <QtWidgets/QMainWindow>
#include "ui_vibraplotter.h"
#include "ui_newProject.h"
#include "ui_loadProject.h"
#include "ui_saveProject.h"
#include "ui_settings.h"
#include <qvector.h>
#include <fstream>
#include <iostream>
#include <time.h>       /* time */
#include <QtXml\qxml.h>
#include <QtXml\qdom.h>
#include <qdir.h>
#include "communication_manager.h"
#include <qprogressdialog.h>
#include <QtSerialPort\qserialportinfo.h>

class VibraPlotter : public QMainWindow
{
	Q_OBJECT

public:
	VibraPlotter(QWidget *parent = 0);
	~VibraPlotter();

private:

	QVector<double> Fourier_Calc(QVector<double> In_data);

	void Plot(QCustomPlot *Axes, QVector<double> Xdata, QVector<double> Ydata, QString Xlbl, QString Ylbl,
		double Ymin = 0, double Ymax = 0, double Xmin = 0, double Xmax = 0);

	void MaxMin_QVector(QVector<double> A, double &maxA, double &minA);

	void ReadBinFile(QString Path_File);

	bool ValidateNumber(const QString &Input);

	void GetDateTime();

	void ValidateCommentArray();

	void SaveXML();

	void SaveTxtData();

	void SaveBinData();

	void LoadSaveProjectsDIR();

	void LoadXML(QString XMLpath, bool flag_global_copy);

	void ListSerialPorts();

	void UpdateSensitivityTable(QTableWidget *Table);

	//Variables
	QVector<QVector<double>> Channels;
	QVector<QVector<double>> FChannels;
	QVector<double> Time_vec;
	QVector<double> Freq_vec;

	bool dataLoaded;
	int curr_ch_idx;
	QString projSavePath;
	QString mainSavePath;
	QVector<QString> savedProjects;
	int NChannels_proj;
	double RecTime_proj;
	bool projOpened;
	QStringList portList;
		
	//Main Gui
	Ui::VibraPlotterClass ui;
	Ui_VibraPlotterClass * gui;

	//New Project Dialog
	QDialog *newProject;
	Ui_Dialog *ui_newProject;

	//Load Project Dialog
	QDialog *loadProject;
	Ui_loadProject *ui_loadProject;

	//Save Project Dialog
	QDialog *saveProject;
	Ui_saveProject *ui_saveProject;

	//Ssettings Dialog
	QDialog *settings;
	Ui_settings *ui_settings;

	QString ProjName;
	QVector<double> Sensitivity;
	int Nchannels;
	QString DateTime;
	int Rec_Time;
	QVector<QString> Comments;

	//Comunnication variables
	QVector<uchar> bytes_to_save;

	CommunicationManager *serial_manager;

	adq_status_t adq_status = _NONE;

	// Bandera para definir si los paquetes ya estan listos para ser leidos.
	bool packages_made;

	// Total de canales para leer
	unsigned char channels_to_read;

	// Total de paquetes para leer
	unsigned short packages_to_read;

	// Numero de paquete actualmente leido.
	unsigned short current_package;

	// Bandera para definir si se estan leyendo los paquetes
	bool reading_packages;

	QProgressDialog *package_progress_dialog;

public slots:
	void loadData();

	void FourierPlot();

	void ShowNewProjectDialog();

	void UpdateTable_new();

	void ValidateAccept_NewProj();

	void Cancel_NewProj();

	void ShowLoadProjectDialog();

	void Accept_LoadProj();

	void Cancel_LoadProj();

	void ShowSaveProjectDialog();

	void AcceptSave();

	void Cancel_SaveProj();

	void ShowSettingsDialog();

	void UpdateTable_set();

	void readData();

	void startADQ();
};

#endif // VIBRAPLOTTER_H
