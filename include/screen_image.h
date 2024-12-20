
#include "ff/ff.h" // Include FatFS header for SD card handling

// File system callbacks
static lv_fs_res_t fatfs_open(void *file_p, const char *path, lv_fs_mode_t mode) {
    FIL *file = (FIL *)file_p;  // Cast file_p to FIL pointer
    BYTE open_mode;

    // Map LVGL open modes to FatFS modes
    if (mode == LV_FS_MODE_WR) {
        open_mode = FA_WRITE | FA_CREATE_ALWAYS;
    } else if (mode == LV_FS_MODE_RD) {
        open_mode = FA_READ;
    } else {
        return LV_FS_RES_UNKNOWN; // Unsupported mode
    }

    // Open the file with FatFS
    FRESULT res = f_open(file, path, open_mode);
    if (res != FR_OK) {
        return LV_FS_RES_UNKNOWN; // Return an LVGL error if FatFS fails
    }

    return LV_FS_RES_OK; // Success
}

static lv_fs_res_t fatfs_read(void *file_p, void *buf, uint32_t btr, uint32_t *br) {
    // Cast file_p to FIL pointer
    FIL *file = (FIL *)file_p;

    // Use FatFS's f_read to read the data
    FRESULT res = f_read(file, buf, btr, (UINT *)br);

    // Return appropriate result based on FatFS's result
    return (res == FR_OK) ? LV_FS_RES_OK : LV_FS_RES_UNKNOWN;
}

static lv_fs_res_t fatfs_close(void *file_p) {
    // Cast file_p to FIL pointer and close it
    FIL *file = (FIL *)file_p;
    f_close(file);
    return LV_FS_RES_OK;
}

void register_card() {

    lv_fs_drv_t fs_drv;


    memset(&fs_drv, 0, sizeof(lv_fs_drv_t)); // Manually initialize for older versions
    lv_fs_init();

    fs_drv.file_size = sizeof(FIL);
    fs_drv.letter = 'S';  // Assign a letter for your filesystem
    fs_drv.open = fatfs_open;
    fs_drv.close = fatfs_close;
    fs_drv.read = fatfs_read;

    // Register the driver
    lv_fs_add_drv(&fs_drv);


    lv_obj_t * img;

    img = lv_img_create(lv_scr_act(), NULL);

    
    /* Assuming a File system is attached to letter 'A'
     * E.g. set LV_USE_FS_STDIO 'A' in lv_conf.h */
    lv_img_set_src(img, "S:/usd/img.bin");
    lv_obj_align(img, NULL, LV_ALIGN_CENTER, 0, 0); // Center the image

}