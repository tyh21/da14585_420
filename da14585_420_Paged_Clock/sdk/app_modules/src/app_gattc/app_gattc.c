/**
 ****************************************************************************************
 *
 * @file app_gattc.c
 *
 * @brief Generic Attribute Profile Service Application entry point
 *
 * Copyright (C) 2018-2019 Dialog Semiconductor.
 * This computer program includes Confidential, Proprietary Information
 * of Dialog Semiconductor. All Rights Reserved.
 *
 ****************************************************************************************
 */

/**
 ****************************************************************************************
 * @addtogroup APP
 * @{
 ****************************************************************************************
 */

/*
 * INCLUDE FILES
 ****************************************************************************************
 */
#include "rwip_config.h"     // SW configuration

#if (BLE_APP_PRESENT)

#if (BLE_GATT_CLIENT)

#include "app_gattc.h"
#include "app.h"
#include "app_task.h"
#include "gatt_client_task.h"
#include "app_prf_perm_types.h"
#include "user_profiles_config.h"

/*
 * GLOBAL FUNCTION DEFINITIONS
 ****************************************************************************************
 */

void app_gattc_init(void)
{
    // Nothing to do
}

void app_gattc_create_task(void)
{
    struct gapm_profile_task_add_cmd *req = KE_MSG_ALLOC(GAPM_PROFILE_TASK_ADD_CMD,
                                                         TASK_GAPM,
                                                         TASK_APP,
                                                         gapm_profile_task_add_cmd);

    // Fill the message
    req->operation   = GAPM_PROFILE_TASK_ADD;
    req->sec_lvl     = get_user_prf_srv_perm(TASK_ID_GATT_CLIENT);
    req->prf_task_id = TASK_ID_GATT_CLIENT;
    req->app_task    = TASK_APP;
    req->start_hdl   = 0;

    // Send the message
    ke_msg_send(req);
}

void app_gattc_enable(uint8_t conidx)
{
    struct gatt_client_env_tag *gatt_env = PRF_ENV_GET(GATT_CLIENT, gatt_client);
    struct gatt_client_enable_req *req = KE_MSG_ALLOC(GATT_CLIENT_ENABLE_REQ,
                                                      prf_src_task_get(&gatt_env->prf_env, conidx),
                                                      TASK_APP,
                                                      gatt_client_enable_req);

    // Provide the connection type
    req->con_type = PRF_CON_DISCOVERY;

    // Send the message
    ke_msg_send(req);
}

void app_gattc_read_ind_cfg(uint8_t conidx)
{
    struct gatt_client_env_tag *gatt_env = PRF_ENV_GET(GATT_CLIENT, gatt_client);

    struct gatt_client_rd_cfg_ind_req *req = KE_MSG_ALLOC(GATT_CLIENT_RD_CFG_IND_REQ,
                                                      prf_src_task_get(&gatt_env->prf_env, conidx),
                                                      TASK_APP,
                                                      gatt_client_rd_cfg_ind_req);

    ke_msg_send(req);
}

void app_gattc_write_ind_cfg(uint8_t conidx, bool enable)
{
    struct gatt_client_env_tag *gatt_env = PRF_ENV_GET(GATT_CLIENT, gatt_client);

    struct gatt_client_wr_cfg_ind_req *req = KE_MSG_ALLOC(GATT_CLIENT_WR_CFG_IND_REQ,
                                                      prf_src_task_get(&gatt_env->prf_env, conidx),
                                                      TASK_APP,
                                                      gatt_client_wr_cfg_ind_req);

    req->cfg_val = (enable) ? PRF_CLI_START_IND : PRF_CLI_STOP_NTFIND;
    ke_msg_send(req);
}

#endif // (BLE_GATT_CLIENT)

#endif // BLE_APP_PRESENT

/// @} APP
