// SPDX-License-Identifier: GPL-2.0-only
/*
 * Copyright (C) 2021-2022 HandsomeMod Project
 *
 * Handsomeyingyan <handsomeyingyan@gmail.com>
 *
 * GC(Gadget Controller) is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later version.
 *
 */


#include "gc_ffs.h"

int gc_ffs_create(int argc,char *argv[],gc_generic_info info)
{
    usbg_gadget *gadget = gc_init(info);

    if(gadget == NULL)
        return GC_FAILED;

    usbg_function *f_ffs;
    int usbg_ret;

    char *id = gc_generate_id(USBG_F_FFS);

    if(id == NULL)
        return GC_FAILED;

    usbg_ret = usbg_create_function(gadget,USBG_F_FFS,id,NULL,&f_ffs);
    if(usbg_ret != USBG_SUCCESS){
        fprintf(stderr,"failed to create ffs function!  (maybe kernel module not loaded?) \n");
        gc_clean();
        return GC_FAILED;
    }

    /* for now we only create one config file */
    usbg_config *config = gc_get_config(gadget);


    usbg_ret = usbg_add_config_function(config,id,f_ffs);
    if(usbg_ret != USBG_SUCCESS){
        fprintf(stderr,"failed to bind ffs config to function! \n");
        gc_clean();
        return GC_FAILED;
    }

    gc_clean();
    return GC_SUCCESS;
}
