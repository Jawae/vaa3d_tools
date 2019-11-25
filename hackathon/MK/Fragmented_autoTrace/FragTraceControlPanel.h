#ifndef _FRAGTRACECONTROLPANEL_H_
#define _FRAGTRACECONTROLPANEL_H_

#include "v3d_interface.h"

#include "ui_fragmentedTraceUI.h"
#include "FragTraceManager.h"

class FragTraceControlPanel : public QDialog
{
	Q_OBJECT

public:
	FragTraceControlPanel(QWidget* parent, V3DPluginCallback2* callback);

	// ======= Saving path for results / intermediate results ======= //
	QString saveSWCFullName;
	QString adaSaveRoot;
	QString histMaskRoot;
	// ============================================================== //


	/* ======= Result and Scaling Functions ======= */ 
	NeuronTree tracedTree;
	map<string, NeuronTree> tracedTrees;
	void scaleTracedTree();
	NeuronTree treeScaleBack(const NeuronTree& inputTree);
	/* ============================================ */

	map<string, float> paramsFromUI;

	vector<string> blankAreas; // will be abandoned

signals:
	void switchOnSegPipe(); // currently not in action

public slots:
    /* =========== User Interface Configuration Buttons ============ */
	void imgFmtChecked(bool checked);
	void nestedChecks(bool checked);
	void multiSomaTraceChecked(bool checked);
	void saveSegStepsResultChecked(bool checked);
	void saveSettingsClicked();
	void browseSavePathClicked();
	void blankAreaClicked();
    /* ======= END of [User Interface Configuration Buttons] ======= */

	// ********************************************************************** //
	void traceButtonClicked(); // ==> THIS IS WHERE THE TRACING PROCESS STARTS
	// ********************************************************************** //

	void catchTracedTree(NeuronTree tracedTree) { this->tracedTree = tracedTree; }

private:
	V3DPluginCallback2* thisCallback;
	Ui::FragmentedTraceUI* uiPtr;
	FragTraceManager* traceManagerPtr;

	/* =============== Additional Widget =============== */
	QDoubleSpinBox* doubleSpinBox;
	QStandardItemModel* listViewBlankAreas;
	QStandardItemModel* somaListViewer;
	/* ================================================= */



	/* =============== Parameter Collecting Functions =============== */
	void pa_imgEnhancement();
	void pa_maskGeneration();
	void pa_objFilter();
	void pa_objBasedMST();
	void pa_postElongation();
	/* =========== END of [Parameter Collecting Functions] ========== */



	/* ======= Tracing Volume Preparation ======= */
	// Partial volume tracing is achieved by talking to tf::PluginInterface through V3d_PluginLoader with v3d_interface's virtual [getPartialVolumeCoords],
	// so that it can be directly accessed through [thisCalback] from [teraflyTracePrep].
	bool volumeAdjusted;
	int* volumeAdjustedCoords; // local coordinates of [displaying image boudaries], eg, 1 ~ 256, etc
	int* globalCoords;         // global coordinates of [displaying image boundaries] in whole brain scale, currently not used.
	int* displayingDims;

	void teraflyTracePrep(workMode mode);
	/* ========================================== */

	

	bool markerMonitorSwitch;
	QList<ImageMarker> selectedMarkerList;
	QList<ImageMarker> selectedLocalMarkerList;
	map<int, ImageMarker> somaMap;
	map<int, ImageMarker> localSomaMap;
	map<int, string> somaDisplayNameMap;



	void fillUpParamsForm(); // This is for future parameter learning project.

	void blankArea(); // will be abandoned in newer version



private slots:
	void markerMonitor();
	void refreshSomaCoords();
};


#endif