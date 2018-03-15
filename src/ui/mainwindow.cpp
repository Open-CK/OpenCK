/*
** mainwindow.cpp
**
** Copyright © Beyond Skyrim Development Team, 2017.
** This file is part of OPENCK (https://github.com/Beyond-Skyrim/openck)
**
** OpenCK is free software; this file may be used under the terms of the GNU
** General Public License version 3.0 or later as published by the Free Software
** Foundation and appearing in the file LICENSE.GPL included in the
** packaging of this file.
**
** OpenCK is distributed in the hope that it will be useful,
** but WITHOUT ANY WARRANTY; without even the implied warranty of
** MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
**
** Please review the following information to ensure the GNU General Public
** License version 3.0 requirements will be met:
** http://www.gnu.org/copyleft/gpl.html.
**
** You should have received a copy of the GNU General Public License version
** 3.0 along with OpenCK; if not, write to the Free Software Foundation,
** Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
**
** Created Date: 04-Jul-2017
*/

#include <ui/mainwindow.h>
#include "ui_mainwindow.h"

#include <QActionGroup>

#include <ui/scriptmanagertab.h>

//!@file mainwindow.cpp Source for the Main UI Window.

/**
 * Creates a MainWindow object with appropriate information.
 * @brief Creates and sets up the Main Window.
 * @param parent The parent widget of the main window.
 */
MainWindow::MainWindow(QWidget* parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    //Begin UI initialization
    ui->setupUi(this);
    renderWindow = new RenderWindow(this);
    ui->verticalLayoutLevelDesignRender->addWidget(renderWindow);

    QActionGroup* viewMode = new QActionGroup(this);
    viewMode->addAction(ui->actionImplementation);
    viewMode->addAction(ui->actionLevelDesign);
    viewMode->addAction(ui->actionMessages);
    viewMode->addAction(ui->actionSpreadsheet);
	viewMode->addAction(ui->actionScriptManager);
	ui->stackedWidgetViewMode->setCurrentIndex(0);

    //Initialise file model
    QStringList headers;
    headers.append("Form ID");
    headers.append("Editor ID");
    fileModel = new models::FileModel(headers);

    //Initialise form model
    headers.clear();
    headers.append("");
    headers.append("File");
    formModel = new models::FormModel(headers);

    //Initialise parser and signal/slot connections
    io::Parser::getParser().init(fileModel, formModel);
    connect(&io::Parser::getParser(), &io::Parser::updateFileModel, this, &MainWindow::updateFileModel);

    //Link data models to UI views
    ui->treeViewImplementation->setModel(fileModel);
    ui->recordViewImplementation->setModel(formModel);
    ui->recordViewImplementation->setHeaderHidden(false);
}

/**
 * Destructs the Main Window by deleting the pointer to the UI in memory.
 * @brief Destructs the main Window.
 */
MainWindow::~MainWindow()
{
    delete ui;
}

/**
 * Method called when File->Data is pressed, creating the data window.
 * @brief Creates the data window.
 * @see datawindow.cpp
 */
void MainWindow::on_actionData_triggered()
{
    dataWindow = new DataWindow;
    dataWindow->exec();
}

/**
 * Method called when File->Save is pressed, [explanation]
 * @brief MainWindow::on_actionSave_triggered()
 */
void MainWindow::on_actionSave_triggered()
{
    //TODO
}

/**
 * Method called when File->Export is pressed, [explanation]
 * @brief MainWindow::on_actionExport_triggered()
 */
void MainWindow::on_actionExport_triggered()
{
    //TODO
}

/**
 * Method called when File->Preferences is pressed, [explanation]
 * @brief MainWindow::on_actionPreferences_triggered()
 */
void MainWindow::on_actionPreferences_triggered()
{
    //TODO
}

/**
 * Method called when File->Validate Loaded Data is pressed, [explanation]
 * @brief MainWindow::on_actionValidate_Loaded_Data_triggered()
 */
void MainWindow::on_actionValidate_Loaded_Data_triggered()
{
    //TODO
}

/**
 * Method called when File->Create Archive is pressed, [explanation]
 * @brief MainWindow::on_actionCreate_Archive_triggered()
 */
void MainWindow::on_actionCreate_Archive_triggered()
{
    //TODO
}

/**
 * Method called when File->Upload Active Plugin to Steam is pressed, [explanation]
 * @brief MainWindow::on_actionUpload_Active_Plugin_to_Steam_triggered()
 */
void MainWindow::on_actionUpload_Active_Plugin_to_Steam_triggered()
{
    //TODO
}

/**
 * Method called when the File->Exit button is pressed which exits the app.
 * @brief Exits the application.
 */
void MainWindow::on_actionExit_triggered()
{
    qDebug() << tr("User hit exit from File menu");
    close();
}

/**
 * Method called when Edit->Undo is pressed, [explanation]
 * @brief MainWindow::on_actionUndo_triggered()
 */
void MainWindow::on_actionUndo_triggered()
{
    //TODO
}

/**
 * Method called when Edit->Redo is pressed, [explanation]
 * @brief MainWindow::on_actionRedo_triggered()
 */
void MainWindow::on_actionRedo_triggered()
{
    //TODO
}

/**
 * Method called when Edit->Cut Render is pressed, [explanation]
 * @brief MainWindow::on_actionCut_Render_triggered()
 */
void MainWindow::on_actionCut_Render_triggered()
{
    //TODO
}

/**
 * Method called when Edit->Copy Render is pressed, [explanation]
 * @brief MainWindow::on_actionCopy_Render_triggered()
 */
void MainWindow::on_actionCopy_Render_triggered()
{
    //TODO
}

/**
 * Method called when Edit->Paste Render is pressed, [explanation]
 * @brief MainWindow::on_actionPaste_Render_triggered()
 */
void MainWindow::on_actionPaste_Render_triggered()
{
    //TODO
}

/**
 * Method called when Edit->Paste in Place is pressed, [explanation]
 * @brief MainWindow::on_actionPaste_in_Place_triggered()
 */
void MainWindow::on_actionPaste_in_Place_triggered()
{
    //TODO
}

/**
 * Method called when Edit->Duplicate is pressed, [explanation]
 * @brief MainWindow::on_actionDuplicate_triggered()
 */
void MainWindow::on_actionDuplicate_triggered()
{
    //TODO
}

/**
 * Method called when Edit->Search and Replace is pressed, [explanation]
 * @brief MainWindow::on_actionSearch_and_Replace_triggered()
 */
void MainWindow::on_actionSearch_and_Replace_triggered()
{
    //TODO
}

/**
 * Method called when Edit->Find Text is pressed, [explanation]
 * @brief MainWindow::on_actionFind_Text_triggered()
 */
void MainWindow::on_actionFind_Text_triggered()
{
    //TODO
}

/**
 * Method called when Edit->Render Window Hotkeys is pressed, [explanation]
 * @brief MainWindow::on_actionRender_Window_Hotkeys_triggered()
 */
void MainWindow::on_actionRender_Window_Hotkeys_triggered()
{
    //TODO
}

/**
 * Method called when Edit->Render Window Preferences is pressed, [explanation]
 * @brief MainWindow::on_actionRender_Window_Preferences_triggered()
 */
void MainWindow::on_actionRender_Window_Preferences_triggered()
{
    //TODO
}

/**
 * Method called when View->Toolbar is pressed, [explanation]
 * @brief MainWindow::on_actionToolbar_triggered()
 */
void MainWindow::on_actionToolbar_triggered()
{
    //TODO
}

/**
 * Method called when View->Statusbar is pressed, [explanation]
 * @brief MainWindow::on_actionStatusbar_triggered()
 */
void MainWindow::on_actionStatusbar_triggered()
{
    //TODO
}

/**
 * Method called when View->Open Windows is pressed, [explanation]
 * @brief MainWindow::on_actionOpen_Windows_triggered()
 */
void MainWindow::on_actionOpen_Windows_triggered()
{
    //TODO
}

/**
 * Method called when View->Object Window is pressed, [explanation]
 * @brief MainWindow::on_actionObject_Window_triggered()
 */
void MainWindow::on_actionObject_Window_triggered()
{
    //TODO
}

/**
 * Method called when View->Cell View Window is pressed, [explanation]
 * @brief MainWindow::on_actionCell_View_Window_triggered()
 */
void MainWindow::on_actionCell_View_Window_triggered()
{
    //TODO
}

/**
 * Method called when View->Scene Info Window is pressed, [explanation]
 * @brief MainWindow::on_actionScene_Info_Window_triggered()
 */
void MainWindow::on_actionScene_Info_Window_triggered()
{
    //TODO
}

/**
 * Method called when View->Preview Window is pressed, [explanation]
 * @brief MainWindow::on_actionPreview_Window_triggered()
 */
void MainWindow::on_actionPreview_Window_triggered()
{
    //TODO
}

/**
 * Method called when View->Show Hide Window is pressed, [explanation]
 * @brief MainWindow::on_actionShow_Hide_Window_triggered()
 */
void MainWindow::on_actionShow_Hide_Window_triggered()
{
    //TODO
}

/**
 * Method called when View->Reference Batch Action Window is pressed, [explanation]
 * @brief MainWindow::on_actionReference_Batch_Action_Window_triggered()
 */
void MainWindow::on_actionReference_Batch_Action_Window_triggered()
{
    //TODO
}

/**
 * Method called when View->Current Cell Only is pressed, [explanation]
 * @brief MainWindow::on_actionCurrent_Cell_Only_triggered()
 */
void MainWindow::on_actionCurrent_Cell_Only_triggered()
{
    //TODO
}

/**
 * Method called when View->Markers is pressed, [explanation]
 * @brief MainWindow::on_actionMarkers_triggered()
 */
void MainWindow::on_actionMarkers_triggered()
{
    //TODO
}

/**
 * Method called when View->Light Markers is pressed, [explanation]
 * @brief MainWindow::on_actionLight_Markers_triggered()
 */
void MainWindow::on_actionLight_Markers_triggered()
{
    //TODO
}

/**
 * Method called when View->Sound Markers is pressed, [explanation]
 * @brief MainWindow::on_actionSound_Markers_triggered()
 */
void MainWindow::on_actionSound_Markers_triggered()
{
    //TODO
}

/**
 * Method called when View->Light Radius is pressed, [explanation]
 * @brief MainWindow::on_actionLight_Radius_triggered()
 */
void MainWindow::on_actionLight_Radius_triggered()
{
    //TODO
}

/**
 * Method called when View->Wireframe is pressed, [explanation]
 * @brief MainWindow::on_actionWireframe_triggered()
 */
void MainWindow::on_actionWireframe_triggered()
{
    //TODO
}

/**
 * Method called when View->Sky is pressed, [explanation]
 * @brief MainWindow::on_actionSky_triggered()
 */
void MainWindow::on_actionSky_triggered()
{
    //TODO
}

/**
 * Method called when View->Grass is pressed, [explanation]
 * @brief MainWindow::on_actionGrass_triggered()
 */
void MainWindow::on_actionGrass_triggered()
{
    //TODO
}

/**
 * Method called when View->Fog is pressed, [explanation]
 * @brief MainWindow::on_actionFog_triggered()
 */
void MainWindow::on_actionFog_triggered()
{
    //TODO
}

/**
 * Method called when View->Leaves is pressed, [explanation]
 * @brief MainWindow::on_actionLeaves_triggered()
 */
void MainWindow::on_actionLeaves_triggered()
{
    //TODO
}

/**
 * Method called when View->Trees is pressed, [explanation]
 * @brief MainWindow::on_actionTrees_triggered()
 */
void MainWindow::on_actionTrees_triggered()
{
    //TODO
}

/**
 * Method called when View->Collision Geometry is pressed, [explanation]
 * @brief MainWindow::on_actionCollision_Geometry_triggered()
 */
void MainWindow::on_actionCollision_Geometry_triggered()
{
    //TODO
}

/**
 * Method called when View->Occlusion Planes is pressed, [explanation]
 * @brief MainWindow::on_actionOcclusion_Planes_triggered()
 */
void MainWindow::on_actionOcclusion_Planes_triggered()
{
    //TODO
}

/**
 * Method called when View->Isometric is pressed, [explanation]
 * @brief MainWindow::on_actionIsometric_triggered()
 */
void MainWindow::on_actionIsometric_triggered()
{
    //TODO
}

/**
 * Method called when View->Top is pressed, [explanation]
 * @brief MainWindow::on_actionTop_triggered()
 */
void MainWindow::on_actionTop_triggered()
{
    //TODO
}

/**
 * Method called when View->Depth Biasing is pressed, [explanation]
 * @brief MainWindow::on_actionDepth_Biasing_triggered()
 */
void MainWindow::on_actionDepth_Biasing_triggered()
{
    //TODO
}

/**
 * Method called when View->Refresh Render Window is pressed, [explanation]
 * @brief MainWindow::on_actionRefresh_Render_Window_triggered()
 */
void MainWindow::on_actionRefresh_Render_Window_triggered()
{
    //TODO
}

/**
 * Method called when View->Warnings is pressed, [explanation]
 * @brief MainWindow::on_actionWarnings_triggered()
 */
void MainWindow::on_actionWarnings_triggered()
{
    //TODO
}

/**
 * Method called when World->World Spaces is pressed, [explanation]
 * @brief MainWindow::on_actionWorld_Spaces_triggered()
 */
void MainWindow::on_actionWorld_Spaces_triggered()
{
    //TODO
}

/**
 * Method called when World->Regions is pressed, [explanation]
 * @brief MainWindow::on_actionRegions_triggered()
 */
void MainWindow::on_actionRegions_triggered()
{
    //TODO
}

/**
 * Method called when World->Cells is pressed, [explanation]
 * @brief MainWindow::on_actionCells_triggered()
 */
void MainWindow::on_actionCells_triggered()
{
    //TODO
}

/**
 * Method called when World->World LOD is pressed, [explanation]
 * @brief MainWindow::on_actionWorld_LOD_triggered()
 */
void MainWindow::on_actionWorld_LOD_triggered()
{
    //TODO
}

/**
 * Method called when World->TODO is pressed, [explanation]
 * @brief MainWindow::on_actionTODO_triggered()
 */
void MainWindow::on_actionTODO_triggered()
{
    //TODO
}

/**
 * Method called when World->Test Icons Textures is pressed, [explanation]
 * @brief MainWindow::on_actionTest_Icons_Textures_triggered()
 */
void MainWindow::on_actionTest_Icons_Textures_triggered()
{
    //TODO
}

/**
 * Method called when World->Test All Cells is pressed, [explanation]
 * @brief MainWindow::on_actionTest_All_Cells_triggered()
 */
void MainWindow::on_actionTest_All_Cells_triggered()
{
    //TODO
}

/**
 * Method called when World->Test Interior Cells is pressed, [explanation]
 * @brief MainWindow::on_actionTest_Interior_Cells_triggered()
 */
void MainWindow::on_actionTest_Interior_Cells_triggered()
{
    //TODO
}

/**
 * Method called when World->Output Model Size List is pressed, [explanation]
 * @brief MainWindow::on_actionOutput_Model_Size_List_triggered()
 */
void MainWindow::on_actionOutput_Model_Size_List_triggered()
{
    //TODO
}

/**
 * Method called when World->View Render Test Failures is pressed, [explanation]
 * @brief MainWindow::on_actionView_Render_Test_Failures_triggered()
 */
void MainWindow::on_actionView_Render_Test_Failures_triggered()
{
    //TODO
}

/**
 * Method called when World->View BetaComment Data is pressed, [explanation]
 * @brief MainWindow::on_actionView_BetaComment_Data_triggered()
 */
void MainWindow::on_actionView_BetaComment_Data_triggered()
{
    //TODO
}

/**
 * Method called when World->Run Havok Sim is pressed, [explanation]
 * @brief MainWindow::on_actionRun_Havok_Sim_triggered()
 */
void MainWindow::on_actionRun_Havok_Sim_triggered()
{
    //TODO
}

/**
 * Method called when World->Update Lighting and Effects is pressed, [explanation]
 * @brief MainWindow::on_actionUpdate_Lighting_and_Effects_triggered()
 */
void MainWindow::on_actionUpdate_Lighting_and_Effects_triggered()
{
    //TODO
}

/**
 * Method called when World->Landscape Editing is pressed, [explanation]
 * @brief MainWindow::on_actionLandscape_Editing_triggered()
 */
void MainWindow::on_actionLandscape_Editing_triggered()
{
    //TODO
}

/**
 * Method called when World->Object Palette Editing is pressed, [explanation]
 * @brief MainWindow::on_actionObject_Palette_Editing_triggered()
 */
void MainWindow::on_actionObject_Palette_Editing_triggered()
{
    //TODO
}

/**
 * Method called when World->Heightmap Editing is pressed, [explanation]
 * @brief MainWindow::on_actionHeightmap_Editing_triggered()
 */
void MainWindow::on_actionHeightmap_Editing_triggered()
{
    //TODO
}

/**
 * Method called when World->Create Local Maps is pressed, [explanation]
 * @brief MainWindow::on_actionCreate_Local_Maps_triggered()
 */
void MainWindow::on_actionCreate_Local_Maps_triggered()
{
    //TODO
}

/**
 * Method called when World->Validate Room Portal Alignment is pressed, [explanation]
 * @brief MainWindow::on_actionValidate_Room_Portal_Alignment_triggered()
 */
void MainWindow::on_actionValidate_Room_Portal_Alignment_triggered()
{
    //TODO
}

/**
 * Method called when World->Align Tangent Space at NIF Intersection is pressed, [explanation]
 * @brief MainWindow::on_actionAlign_Tangent_Space_at_NIF_Intersection_triggered()
 */
void MainWindow::on_actionAlign_Tangent_Space_at_NIF_Intersection_triggered()
{
    //TODO
}

/**
 * Method called when World->Generate LOS is pressed, [explanation]
 * @brief MainWindow::on_actionGenerate_LOS_triggered()
 */
void MainWindow::on_actionGenerate_LOS_triggered()
{
    //TODO
}

/**
 * Method called when World->Generate Max Height Data For Current Cell is pressed, [explanation]
 * @brief MainWindow::on_actionGenerate_Max_Height_Data_For_Current_Cell_triggered()
 */
void MainWindow::on_actionGenerate_Max_Height_Data_For_Current_Cell_triggered()
{
    //TODO
}

/**
 * Method called when World->Generate Max Height Data For World is pressed, [explanation]
 * @brief MainWindow::on_actionGenerate_Max_Height_Data_For_World_triggered()
 */
void MainWindow::on_actionGenerate_Max_Height_Data_For_World_triggered()
{
    //TODO
}

/**
 * Method called when World->Generate Max Height Data For ALL Worlds is pressed, [explanation]
 * @brief MainWindow::on_actionGenerate_Max_Height_Data_For_ALL_Worlds_triggered()
 */
void MainWindow::on_actionGenerate_Max_Height_Data_For_ALL_Worlds_triggered()
{
    //TODO
}

/**
 * Method called when NavMesh->Object Based Generation is pressed, [explanation]
 * @brief MainWindow::on_actionObject_Based_Generation_triggered()
 */
void MainWindow::on_actionObject_Based_Generation_triggered()
{
    //TODO
}

/**
 * Method called when NavMesh->Havok Based Generation is pressed, [explanation]
 * @brief MainWindow::on_actionHavok_Based_Generation_triggered()
 */
void MainWindow::on_actionHavok_Based_Generation_triggered()
{
    //TODO
}

/**
 * Method called when NavMesh->Recast Based Generation is pressed, [explanation]
 * @brief MainWindow::on_actionRecast_Based_Generation_triggered()
 */
void MainWindow::on_actionRecast_Based_Generation_triggered()
{
    //TODO
}

/**
 * Method called when NavMesh->Advanced is pressed, [explanation]
 * @brief MainWindow::on_actionAdvanced_triggered()
 */
void MainWindow::on_actionAdvanced_triggered()
{
    //TODO
}

/**
 * Method called when NavMesh->Auto Generate WorldSpace is pressed, [explanation]
 * @brief MainWindow::on_actionAuto_Generate_WorldSpace_triggered()
 */
void MainWindow::on_actionAuto_Generate_WorldSpace_triggered()
{
    //TODO
}

/**
 * Method called when NavMesh->Check NavMeshes is pressed, [explanation]
 * @brief MainWindow::on_actionCheck_NavMeshes_triggered()
 */
void MainWindow::on_actionCheck_NavMeshes_triggered()
{
    //TODO
}

/**
 * Method called when NavMesh->Finalize Cell NavMeshes is pressed, [explanation]
 * @brief MainWindow::on_actionFinalize_Cell_NavMeshes_triggered()
 */
void MainWindow::on_actionFinalize_Cell_NavMeshes_triggered()
{
    //TODO
}

/**
 * Method called when NavMesh->Find Cover Edges is pressed, [explanation]
 * @brief MainWindow::on_actionFind_Cover_Edges_triggered()
 */
void MainWindow::on_actionFind_Cover_Edges_triggered()
{
    //TODO
}

/**
 * Method called when NavMesh->Move Selection to Separate NavMesh is pressed, [explanation]
 * @brief MainWindow::on_actionMove_Selection_to_Separate_NavMesh_triggered()
 */
void MainWindow::on_actionMove_Selection_to_Separate_NavMesh_triggered()
{
    //TODO
}

/**
 * Method called when NavMesh->NavMesh Draw Mode is pressed, [explanation]
 * @brief MainWindow::on_actionNavMesh_Draw_Mode_triggered()
 */
void MainWindow::on_actionNavMesh_Draw_Mode_triggered()
{
    //TODO
}

/**
 * Method called when NavMesh->Draw Cover is pressed, [explanation]
 * @brief MainWindow::on_actionDraw_Cover_triggered()
 */
void MainWindow::on_actionDraw_Cover_triggered()
{
    //TODO
}

/**
 * Method called when NavMesh->Clear Generated Cover is pressed, [explanation]
 * @brief MainWindow::on_actionClear_Generated_Cover_triggered()
 */
void MainWindow::on_actionClear_Generated_Cover_triggered()
{
    //TODO
}

/**
 * Method called when NavMesh->Clear Cover is pressed, [explanation]
 * @brief MainWindow::on_actionClear_Cover_triggered()
 */
void MainWindow::on_actionClear_Cover_triggered()
{
    //TODO
}

/**
 * Method called when NavMesh->Remove Cell NavMeshes is pressed, [explanation]
 * @brief MainWindow::on_actionRemove_Cell_NavMeshes_triggered()
 */
void MainWindow::on_actionRemove_Cell_NavMeshes_triggered()
{
    //TODO
}

/**
 * Method called when NavMesh->Check WorldSpace Cells for Finalize is pressed, [explanation]
 * @brief MainWindow::on_actionCheck_WorldSpace_Cells_for_Finalize_triggered()
 */
void MainWindow::on_actionCheck_WorldSpace_Cells_for_Finalize_triggered()
{
    //TODO
}

/**
 * Method called when NavMesh->Finalize WorldSpace is pressed, [explanation]
 * @brief MainWindow::on_actionFinalize_WorldSpace_triggered()
 */
void MainWindow::on_actionFinalize_WorldSpace_triggered()
{
    //TODO
}

/**
 * Method called when NavMesh->Force Finalize Full WorldSpace is pressed, [explanation]
 * @brief MainWindow::on_actionForce_Finalize_Full_WorldSpace_triggered()
 */
void MainWindow::on_actionForce_Finalize_Full_WorldSpace_triggered()
{
    //TODO
}

/**
 * Method called when NavMesh->Finalize All Interiors is pressed, [explanation]
 * @brief MainWindow::on_actionFinalize_All_Interiors_triggered()
 */
void MainWindow::on_actionFinalize_All_Interiors_triggered()
{
    //TODO
}

/**
 * Method called when NavMesh->Force Finalize All Spaces is pressed, [explanation]
 * @brief MainWindow::on_actionForce_Finalize_All_Spaces_triggered()
 */
void MainWindow::on_actionForce_Finalize_All_Spaces_triggered()
{
    //TODO
}

/**
 * Method called when NavMesh->Remove All AutoGen Islands is pressed, [explanation]
 * @brief MainWindow::on_actionRemove_All_AutoGen_Islands_triggered()
 */
void MainWindow::on_actionRemove_All_AutoGen_Islands_triggered()
{
    //TODO
}

/**
 * Method called when NavMesh->Set Cell Auto Generated is pressed, [explanation]
 * @brief MainWindow::on_actionSet_Cell_Auto_Generated_triggered()
 */
void MainWindow::on_actionSet_Cell_Auto_Generated_triggered()
{
    //TODO
}

/**
 * Method called when NavMesh->Clear Cell Auto Generated is pressed, [explanation]
 * @brief MainWindow::on_actionClear_Cell_Auto_Generated_triggered()
 */
void MainWindow::on_actionClear_Cell_Auto_Generated_triggered()
{
    //TODO
}

/**
 * Method called when NavMesh->Audit NavMesh Report is pressed, [explanation]
 * @brief MainWindow::on_actionAudit_NavMesh_Report_triggered()
 */
void MainWindow::on_actionAudit_NavMesh_Report_triggered()
{
    //TODO
}

/**
 * Method called when NavMesh->Normal Pathing Test is pressed, [explanation]
 * @brief MainWindow::on_actionNormal_Pathing_Test_triggered()
 */
void MainWindow::on_actionNormal_Pathing_Test_triggered()
{
    //TODO
}

/**
 * Method called when NavMesh->Cover Test is pressed, [explanation]
 * @brief MainWindow::on_actionCover_Test_triggered()
 */
void MainWindow::on_actionCover_Test_triggered()
{
    //TODO
}

/**
 * Method called when NavMesh->Dodge Test is pressed, [explanation]
 * @brief MainWindow::on_actionDodge_Test_triggered()
 */
void MainWindow::on_actionDodge_Test_triggered()
{
    //TODO
}

/**
 * Method called when NavMesh->Flee Test is pressed, [explanation]
 * @brief MainWindow::on_actionFlee_Test_triggered()
 */
void MainWindow::on_actionFlee_Test_triggered()
{
    //TODO
}

/**
 * Method called when NavMesh->Hide Test is pressed, [explanation]
 * @brief MainWindow::on_actionHide_Test_triggered()
 */
void MainWindow::on_actionHide_Test_triggered()
{
    //TODO
}

/**
 * Method called when NavMesh->LOS Test is pressed, [explanation]
 * @brief MainWindow::on_actionLOS_Test_triggered()
 */
void MainWindow::on_actionLOS_Test_triggered()
{
    //TODO
}

/**
 * Method called when NavMesh->ClosePoint Test is pressed, [explanation]
 * @brief MainWindow::on_actionClosePoint_Test_triggered()
 */
void MainWindow::on_actionClosePoint_Test_triggered()
{
    //TODO
}

/**
 * Method called when NavMesh->Safe StraightLine Test is pressed, [explanation]
 * @brief MainWindow::on_actionSafe_StraightLine_Test_triggered()
 */
void MainWindow::on_actionSafe_StraightLine_Test_triggered()
{
    //TODO
}

/**
 * Method called when NavMesh->Draw Path Only is pressed, [explanation]
 * @brief MainWindow::on_actionDraw_Path_Only_triggered()
 */
void MainWindow::on_actionDraw_Path_Only_triggered()
{
    //TODO
}

/**
 * Method called when NavMesh->Draw Cost is pressed, [explanation]
 * @brief MainWindow::on_actionDraw_Cost_triggered()
 */
void MainWindow::on_actionDraw_Cost_triggered()
{
    //TODO
}

/**
 * Method called when NavMesh->Draw Heuristic is pressed, [explanation]
 * @brief MainWindow::on_actionDraw_Heuristic_triggered()
 */
void MainWindow::on_actionDraw_Heuristic_triggered()
{
    //TODO
}

/**
 * Method called when NavMesh->Draw Fitness is pressed, [explanation]
 * @brief MainWindow::on_actionDraw_Fitness_triggered()
 */
void MainWindow::on_actionDraw_Fitness_triggered()
{
    //TODO
}

/**
 * Method called when NavMesh->Draw PathSmoother Bounds is pressed, [explanation]
 * @brief MainWindow::on_actionDraw_PathSmoother_Bounds_triggered()
 */
void MainWindow::on_actionDraw_PathSmoother_Bounds_triggered()
{
    //TODO
}

/**
 * Method called when NavMesh->Update Obstacle Manager is pressed, [explanation]
 * @brief MainWindow::on_actionUpdate_Obstacle_Manager_triggered()
 */
void MainWindow::on_actionUpdate_Obstacle_Manager_triggered()
{
    //TODO
}

/**
 * Method called when NavMesh->Select Triangle By Index is pressed, [explanation]
 * @brief MainWindow::on_actionSelect_Triangle_By_Index_triggered()
 */
void MainWindow::on_actionSelect_Triangle_By_Index_triggered()
{
    //TODO
}

/**
 * Method called when Character->Actor Values is pressed, [explanation]
 * @brief MainWindow::on_actionActor_Values_triggered()
 */
void MainWindow::on_actionActor_Values_triggered()
{
    //TODO
}

/**
 * Method called when Character->Filtered Dialogue is pressed, [explanation]
 * @brief MainWindow::on_actionFiltered_Dialogue_triggered()
 */
void MainWindow::on_actionFiltered_Dialogue_triggered()
{
    //TODO
}

/**
 * Method called when Character->Export Relationship Data is pressed, [explanation]
 * @brief MainWindow::on_actionExport_Relationship_Data_triggered()
 */
void MainWindow::on_actionExport_Relationship_Data_triggered()
{
    //TODO
}

/**
 * Method called when Character->Export Dialogue is pressed, [explanation]
 * @brief MainWindow::on_actionExport_Dialogue_triggered()
 */
void MainWindow::on_actionExport_Dialogue_triggered()
{
    //TODO
}

/**
 * Method called when Character->Export Scene Scripts is pressed, [explanation]
 * @brief MainWindow::on_actionExport_Scene_Scripts_triggered()
 */
void MainWindow::on_actionExport_Scene_Scripts_triggered()
{
    //TODO
}

/**
 * Method called when Character->List Neutral Emotion Dialogue is pressed, [explanation]
 * @brief MainWindow::on_actionList_Neutral_Emotion_Dialogue_triggered()
 */
void MainWindow::on_actionList_Neutral_Emotion_Dialogue_triggered()
{
    //TODO
}

/**
 * Method called when Character->Quest Voice Asset Totals is pressed, [explanation]
 * @brief MainWindow::on_actionQuest_Voice_Asset_Totals_triggered()
 */
void MainWindow::on_actionQuest_Voice_Asset_Totals_triggered()
{
    //TODO
}

/**
 * Method called when Character->Update NPC Body Type Colors is pressed, [explanation]
 * @brief MainWindow::on_actionUpdate_NPC_Body_Type_Colors_triggered()
 */
void MainWindow::on_actionUpdate_NPC_Body_Type_Colors_triggered()
{
    //TODO
}

/**
 * Method called when Character->Edit Player Dialogue is pressed, [explanation]
 * @brief MainWindow::on_actionEdit_Player_Dialogue_triggered()
 */
void MainWindow::on_actionEdit_Player_Dialogue_triggered()
{
    //TODO
}

/**
 * Method called when Character->Quest Aliases is pressed, [explanation]
 * @brief MainWindow::on_actionQuest_Aliases_triggered()
 */
void MainWindow::on_actionQuest_Aliases_triggered()
{
    //TODO
}

/**
 * Method called when Gameplay->Settings is pressed, [explanation]
 * @brief MainWindow::on_actionSettings_triggered()
 */
void MainWindow::on_actionSettings_triggered()
{
    //TODO
}

/**
 * Method called when Gameplay->Papyrus Script Manager is pressed, [explanation]
 * @brief MainWindow::on_actionPapyrus_Script_Manager_triggered()
 */
void MainWindow::on_actionPapyrus_Script_Manager_triggered()
{
    //TODO
}

/**
 * Method called when Gameplay->Compile Papyrus Scripts is pressed, [explanation]
 * @brief MainWindow::on_actionCompile_Papyrus_Scripts_triggered()
 */
void MainWindow::on_actionCompile_Papyrus_Scripts_triggered()
{
    //TODO
}

/**
 * Method called when Gameplay->Animations is pressed, [explanation]
 * @brief MainWindow::on_actionAnimations_triggered()
 */
void MainWindow::on_actionAnimations_triggered()
{
    //TODO
}

/**
 * Method called when Gameplay->Facial Animation is pressed, [explanation]
 * @brief MainWindow::on_actionFacial_Animation_triggered()
 */
void MainWindow::on_actionFacial_Animation_triggered()
{
    //TODO
}

/**
 * Method called when Gameplay->Camera Paths is pressed, [explanation]
 * @brief MainWindow::on_actionCamera_Paths_triggered()
 */
void MainWindow::on_actionCamera_Paths_triggered()
{
    //TODO
}

/**
 * Method called when Gameplay->Default Objects is pressed, [explanation]
 * @brief MainWindow::on_actionDefault_Objects_triggered()
 */
void MainWindow::on_actionDefault_Objects_triggered()
{
    //TODO
}

/**
 * Method called when Gameplay->Validate Forms is pressed, [explanation]
 * @brief MainWindow::on_actionValidate_Forms_triggered()
 */
void MainWindow::on_actionValidate_Forms_triggered()
{
    //TODO
}

/**
 * Method called when Help->Contents is pressed, opening the site of the Creation Kit.
 * @brief MainWindow::on_actionContents_triggered
 */
void MainWindow::on_actionContents_triggered()
{
    QString link = "http://www.creationkit.com/";
    QDesktopServices::openUrl(QUrl(link));
}

/**
 * Method called when Help->About is pressed, creating a message box with needed info.
 * @brief MainWindow::on_actionAbout_triggered
 */
void MainWindow::on_actionAbout_triggered()
{
    QMessageBox* msgBox;
    msgBox = new QMessageBox;
    msgBox->setSizeIncrement(600,400);
#ifdef OPENCK_REVISION
    msgBox->setText(tr("OpenCK Version %1 Revision %2\n(c) 2017 Beyond Skyrim Development Team\nThis project's source code is viewable at https://github.com/Beyond-Skyrim/OpenCK\nHappy Modding!").arg( OPENCK_VERSION, OPENCK_REVISION ));
#else
    msgBox->setText(tr("OpenCK Version %1\n(c) 2017 Beyond Skyrim Development Team\nThis project's source code is viewable at https://github.com/Beyond-Skyrim/OpenCK\nHappy Modding!").arg( OPENCK_VERSION ));
#endif
    msgBox->setStandardButtons(QMessageBox::Ok);
    msgBox->setWindowIcon(QIcon(":/openck32x32.png"));
    msgBox->exec();
}

void MainWindow::on_actionImplementation_triggered()
{
    ui->stackedWidgetViewMode->setCurrentIndex(0);
}

void MainWindow::on_actionLevelDesign_triggered()
{
    ui->stackedWidgetViewMode->setCurrentIndex(1);
}

void MainWindow::on_actionMessages_triggered()
{
    ui->stackedWidgetViewMode->setCurrentIndex(2);
}

void MainWindow::on_actionSpreadsheet_triggered()
{
    ui->stackedWidgetViewMode->setCurrentIndex(3);
}

void MainWindow::on_actionScriptManager_triggered()
{
	ui->stackedWidgetViewMode->setCurrentIndex(4);
}

/**
 * Method called when an index in the treeView is double clicked.
 * @brief Method called when treeView is double clicked.
 * @param Index clicked.
 */
void MainWindow::on_treeViewImplementation_doubleClicked(const QModelIndex &index)
{   
    models::FileModelItem* item;
    item = fileModel->getItem(index);

    if (item->childCount() == 0) {
        item->formData->readForm();
    }

    ui->recordViewImplementation->expandAll();
}

void MainWindow::updateFileModel()
{
    ui->treeViewImplementation->collapseAll();
}