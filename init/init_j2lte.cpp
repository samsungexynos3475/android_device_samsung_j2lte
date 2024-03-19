/*
   Copyright (c) 2016, The Linux Foundation. All rights reserved.
   Copyright (c) 2017-2020, The LineageOS Project. All rights reserved.

   Redistribution and use in source and binary forms, with or without
   modification, are permitted provided that the following conditions are
   met:
    * Redistributions of source code must retain the above copyright
      notice, this list of conditions and the following disclaimer.
    * Redistributions in binary form must reproduce the above
      copyright notice, this list of conditions and the following
      disclaimer in the documentation and/or other materials provided
      with the distribution.
    * Neither the name of The Linux Foundation nor the names of its
      contributors may be used to endorse or promote products derived
      from this software without specific prior written permission.

   THIS SOFTWARE IS PROVIDED "AS IS" AND ANY EXPRESS OR IMPLIED
   WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF
   MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NON-INFRINGEMENT
   ARE DISCLAIMED.  IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS
   BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
   CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
   SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR
   BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
   WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE
   OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN
   IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#include <android-base/file.h>
#include <android-base/logging.h>
#include <android-base/strings.h>
#include <android-base/properties.h>

#include "init_universal3475.h"

using android::base::GetProperty;
using android::base::ReadFileToString;
using android::base::Trim;

void set_sim_info()
{
    const char *simslot_count_path = "/proc/simslot_count";
    std::string simslot_count;
    
    if (ReadFileToString(simslot_count_path, &simslot_count)) {
        simslot_count = Trim(simslot_count); // strip newline
        property_override("ro.vendor.multisim.simslotcount", simslot_count.c_str());
        property_override("vendor.rild.libpath", "/vendor/lib/libsec-ril.so");
        property_override("persist.radio.multisim.config", "ss");
        if (simslot_count.compare("2") == 0) {
            property_override("vendor.rild.libpath2", "/vendor/lib/libsec-ril-dsds.so");
            property_override("persist.radio.multisim.config", "dsds");
        }
    }
    else {
        LOG(ERROR) << "Could not open '" << simslot_count_path << "'\n";
    }
}

void vendor_load_properties()
{
    std::string bootloader = GetProperty("ro.bootloader", "");

    if (bootloader.find("J200GU") == 0) {
        /* j2ltedx */
        property_override("ro.build.description", "j2ltedx-user 5.1.1 LMY47X J200GUDXU3AQL1 release-keys");
        set_ro_product_prop("device", "j2ltedx");
        set_ro_build_prop("fingerprint", "samsung/j2ltedx/j2lte:5.1.1/LMY47X/J200GUDXU3AQL1:user/release-keys");
        set_ro_product_prop("model", "SM-J200GU");
        set_ro_product_prop("name", "j2ltedx");
        gsm_properties("9,1");
    } else if (bootloader.find("J200G") == 0) {
        /* j2ltedd */
        property_override("ro.build.description", "j2ltedd-user 5.1.1 LMY47X J200GDDU2ARL1 release-keys");
        set_ro_product_prop("device", "j2ltedd");
        set_ro_build_prop("fingerprint", "samsung/j2ltedd/j2lte:5.1.1/LMY47X/J200GDDU2ARL1:user/release-keys");
        set_ro_product_prop("model", "SM-J200G");
        set_ro_product_prop("name", "j2ltedd");
        gsm_properties("9,1");
    } else if (bootloader.find("J200BT") == 0) {
        /* j2ltedtvvj */
        property_override("ro.build.description", "j2ltedtvvj-user 5.1.1 LMY47X J200BTUBS2ARJ1 release-keys");
        set_ro_product_prop("device", "j2ltedtvvj");
        set_ro_build_prop("fingerprint", "samsung/j2ltedtvvj/j2ltedtv:5.1.1/LMY47X/J200BTUBS2ARJ1:user/release-keys");
        set_ro_product_prop("model", "SM-J200BT");
        set_ro_product_prop("name", "j2ltedtvvj");
        gsm_properties("9,1");
    } else if (bootloader.find("J200F") == 0) {
        /* j2ltejv */
        property_override("ro.build.description", "j2ltejv-user 5.1.1 LMY47X J200FXXU3ARL2 release-keys");
        set_ro_product_prop("device", "j2ltejv");
        set_ro_build_prop("fingerprint", "samsung/j2ltejv/j2lte:5.1.1/LMY47X/J200FXXU3ARL2:user/release-keys");
        set_ro_product_prop("model", "SM-J200F");
        set_ro_product_prop("name", "j2ltejv");
        gsm_properties("9,1");
    } else if (bootloader.find("J200M") == 0) {
        /* j2lteub */
        property_override("ro.build.description", "j2lteub-user 5.1.1 LMY47X J200MUBS2ARK7 release-keys");
        set_ro_product_prop("device", "j2lteub");
        set_ro_build_prop("fingerprint", "samsung/j2lteub/j2lte:5.1.1/LMY47X/J200MUBS2ARK7:user/release-keys");
        set_ro_product_prop("model", "SM-J200M");
        set_ro_product_prop("name", "j2lteub");
        gsm_properties("9,1");
    } else if (bootloader.find("J200Y") == 0) {
        /* j2ltezt */
        property_override("ro.build.description", "j2ltezt-user 5.1.1 LMY47X J200YZTS2ARH1 release-keys");
        set_ro_product_prop("device", "j2ltezt");
        set_ro_build_prop("fingerprint", "samsung/j2ltezt/j2lte:5.1.1/LMY47X/J200YZTS2ARH1:user/release-keys");
        set_ro_product_prop("model", "SM-J200Y");
        set_ro_product_prop("name", "j2ltezt");
        gsm_properties("9,1");
    } else {
        gsm_properties("9,1");
    }

    set_sim_info();
    std::string device = GetProperty("ro.product.device", "");
    LOG(ERROR) << "Found bootloader id " << bootloader <<  " setting build properties for "
        << device <<  " device" << std::endl;
}
