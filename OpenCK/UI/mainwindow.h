/*
** mainwindow.h
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

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtDebug>
#include <QMessageBox>
#include <QDesktopServices>
#include <QUrl>
#include "datawindow.h"

namespace Ui
{
    class MainWindow;
}

/**
 * The MainWindow class in the UI.
 * @brief The MainWindow class in the UI.
 */
class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
private slots:

    // menuFile signals
    void on_actionData_triggered();
    void on_actionSave_triggered();
    void on_actionExport_triggered();
    void on_actionPreferences_triggered();
    void on_actionValidate_Loaded_Data_triggered();
    void on_actionCreate_Archive_triggered();
    void on_actionUpload_Active_Plugin_to_Steam_triggered();
    void on_actionExit_triggered();

    // menuEdit signals
    void on_actionUndo_triggered();
    void on_actionRedo_triggered();
    void on_actionCut_Render_triggered();
    void on_actionCopy_Render_triggered();
    void on_actionPaste_Render_triggered();
    void on_actionPaste_in_Place_triggered();
    void on_actionDuplicate_triggered();
    void on_actionSearch_and_Replace_triggered();
    void on_actionFind_Text_triggered();
    void on_actionRender_Window_Hotkeys_triggered();
    void on_actionRender_Window_Preferences_triggered();

    // menuView signals
    void on_actionToolbar_triggered();
    void on_actionStatusbar_triggered();
    void on_actionOpen_Windows_triggered();
    void on_actionObject_Window_triggered();
    void on_actionCell_View_Window_triggered();
    void on_actionScene_Info_Window_triggered();
    void on_actionPreview_Window_triggered();
    void on_actionShow_Hide_Window_triggered();
    void on_actionReference_Batch_Action_Window_triggered();
    void on_actionCurrent_Cell_Only_triggered();
    void on_actionMarkers_triggered();
    void on_actionLight_Markers_triggered();
    void on_actionSound_Markers_triggered();
    void on_actionLight_Radius_triggered();
    void on_actionWireframe_triggered();
    void on_actionSky_triggered();
    void on_actionGrass_triggered();
    void on_actionFog_triggered();
    void on_actionLeaves_triggered();
    void on_actionTrees_triggered();
    void on_actionCollision_Geometry_triggered();
    void on_actionOcclusion_Planes_triggered();
    void on_actionIsometric_triggered();
    void on_actionTop_triggered();
    void on_actionDepth_Biasing_triggered();
    void on_actionRefresh_Render_Window_triggered();
    void on_actionWarnings_triggered();

    // menuWorld signals
    void on_actionWorld_Spaces_triggered();
    void on_actionRegions_triggered();
    void on_actionCells_triggered();
    void on_actionWorld_LOD_triggered();
    void on_actionTODO_triggered();
    void on_actionTest_Icons_Textures_triggered();
    void on_actionTest_All_Cells_triggered();
    void on_actionTest_Interior_Cells_triggered();
    void on_actionOutput_Model_Size_List_triggered();
    void on_actionView_Render_Test_Failures_triggered();
    void on_actionView_BetaComment_Data_triggered();
    void on_actionRun_Havok_Sim_triggered();
    void on_actionUpdate_Lighting_and_Effects_triggered();
    void on_actionLandscape_Editing_triggered();
    void on_actionObject_Palette_Editing_triggered();
    void on_actionHeightmap_Editing_triggered();
    void on_actionCreate_Local_Maps_triggered();
    void on_actionValidate_Room_Portal_Alignment_triggered();
    void on_actionAlign_Tangent_Space_at_NIF_Intersection_triggered();
    void on_actionGenerate_LOS_triggered();
    void on_actionGenerate_Max_Height_Data_For_Current_Cell_triggered();
    void on_actionGenerate_Max_Height_Data_For_World_triggered();
    void on_actionGenerate_Max_Height_Data_For_ALL_Worlds_triggered();

    // menuNavMesh signals
    void on_actionObject_Based_Generation_triggered();
    void on_actionHavok_Based_Generation_triggered();
    void on_actionRecast_Based_Generation_triggered();
    void on_actionAdvanced_triggered();
    void on_actionAuto_Generate_WorldSpace_triggered();
    void on_actionCheck_NavMeshes_triggered();
    void on_actionFinalize_Cell_NavMeshes_triggered();
    void on_actionFind_Cover_Edges_triggered();
    void on_actionMove_Selection_to_Separate_NavMesh_triggered();
    void on_actionNavMesh_Draw_Mode_triggered();
    void on_actionDraw_Cover_triggered();
    void on_actionClear_Generated_Cover_triggered();
    void on_actionClear_Cover_triggered();
    void on_actionRemove_Cell_NavMeshes_triggered();
    void on_actionCheck_WorldSpace_Cells_for_Finalize_triggered();
    void on_actionFinalize_WorldSpace_triggered();
    void on_actionForce_Finalize_Full_WorldSpace_triggered();
    void on_actionFinalize_All_Interiors_triggered();
    void on_actionForce_Finalize_All_Spaces_triggered();
    void on_actionRemove_All_AutoGen_Islands_triggered();
    void on_actionSet_Cell_Auto_Generated_triggered();
    void on_actionClear_Cell_Auto_Generated_triggered();
    void on_actionAudit_NavMesh_Report_triggered();
    void on_actionNormal_Pathing_Test_triggered();
    void on_actionCover_Test_triggered();
    void on_actionDodge_Test_triggered();
    void on_actionFlee_Test_triggered();
    void on_actionHide_Test_triggered();
    void on_actionLOS_Test_triggered();
    void on_actionClosePoint_Test_triggered();
    void on_actionSafe_StraightLine_Test_triggered();
    void on_actionDraw_Path_Only_triggered();
    void on_actionDraw_Cost_triggered();
    void on_actionDraw_Heuristic_triggered();
    void on_actionDraw_Fitness_triggered();
    void on_actionDraw_PathSmoother_Bounds_triggered();
    void on_actionUpdate_Obstacle_Manager_triggered();
    void on_actionSelect_Triangle_By_Index_triggered();

    // menuCharacter signals
    void on_actionActor_Values_triggered();
    void on_actionFiltered_Dialogue_triggered();
    void on_actionExport_Relationship_Data_triggered();
    void on_actionExport_Dialogue_triggered();
    void on_actionExport_Scene_Scripts_triggered();
    void on_actionList_Neutral_Emotion_Dialogue_triggered();
    void on_actionQuest_Voice_Asset_Totals_triggered();
    void on_actionUpdate_NPC_Body_Type_Colors_triggered();
    void on_actionEdit_Player_Dialogue_triggered();
    void on_actionQuest_Aliases_triggered();

    // menuGameplay signals
    void on_actionSettings_triggered();
    void on_actionPapyrus_Script_Manager_triggered();
    void on_actionCompile_Papyrus_Scripts_triggered();
    void on_actionAnimations_triggered();
    void on_actionFacial_Animation_triggered();
    void on_actionCamera_Paths_triggered();
    void on_actionDefault_Objects_triggered();
    void on_actionValidate_Forms_triggered();

    // menuHelp signals
    void on_actionContents_triggered();
    void on_actionAbout_triggered();

private:
    /**
     * Pointer to the Qt generated file from the UI designer.
     * @brief Pointer to the Qt generated UI file.
     */
    Ui::MainWindow* ui;
};

#endif // MAINWINDOW_H
