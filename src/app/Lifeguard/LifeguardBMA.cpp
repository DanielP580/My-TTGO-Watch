#include "LifeguardUtils.h"

#include "Lifeguard.h"
#include "LifeguardBMA.h"
#include "LifeguardUtils.h"

//Tile definition
lv_obj_t * lifeguardBMATile = NULL;

//Textfields definiton
lv_obj_t * lifeguardX_textfield = NULL;
lv_obj_t * lifeguardY_textfield = NULL;
lv_obj_t * lifeguardZ_textfield = NULL;

void LifeguardBMATileSetup(uint32_t tileNum)
{

    //Use new tile num and based on that create new object
    lifeguardBMATile = mainbar_get_tile_obj( tileNum);

    //Add header to top of settings 
    lv_obj_t * header = wf_add_settings_header( lifeguardBMATile, "lifeguard BMA");
    lv_obj_align(header, lifeguardBMATile, LV_ALIGN_IN_TOP_MID, THEME_ICON_PADDING, THEME_ICON_PADDING);

    //X-axis definitions
    lv_obj_t * lifeGuardBMA_Xobj = CreateListObject( lifeguardBMATile, header);
    char xName[] = "X";
    CreateListLabel(lifeGuardBMA_Xobj, xName);

    //Y-axis definitions
    lv_obj_t * lifeGuardBMA_Yobj = CreateListObject( lifeguardBMATile, lifeGuardBMA_Xobj);
    char yName[] = "Y";
    CreateListLabel(lifeGuardBMA_Yobj, yName);

    //Z-axis definitions
    lv_obj_t * lifeGuardBMA_Zobj = CreateListObject( lifeguardBMATile, lifeGuardBMA_Yobj);
    char zName[] = "Z";
    CreateListLabel(lifeGuardBMA_Zobj, zName);
}