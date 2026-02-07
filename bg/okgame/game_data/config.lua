----------------------------------------------------------------------------------------------------------
config = {}
config.archive_file           = "/app0/game_data/game_data.psarc"
config.mount_point            = "/game_data_psarc/"
config.useArchive           = false
config.model_path             = {}
config.texture_path           = {}
config.sound_path             = {}
config.play_style_sensitivity = {}
config.enable_save_data_dialog     = true
config.enable_dummy_save_data_load = false
config.single_play_save_data_dir_name = "slot001"
config.multi_play_save_data_dir_name  = "slot000"
config.single_play_save_data_file_name = "single_player_game.dat"
config.multi_play_save_data_file_name  = "multi_player_game.dat"
config.load_exec_argument_header_for_invitation = "shooting_game_invitation"
config.load_exec_argument_header_for_play_together = "shooting_game_play_together"

----------------------------------------------------------------------------------------------------------

config.play_style_select_time = 10
config.game_ready_time = 3
config.game_play_time = 30
config.timeup_display_time = 3
config.video_recording_notification_display_time = 4
config.np_service_label = 0
config.np_score_board_id = 0
config.enable_longest_name_test = false
config.longestUserName   = "MMMMMMMMMMMMMMMM" -- M x 16 (SCE_USER_SERVICE_MAX_USER_NAME_LENGTH)
config.longestNpOnlineId = "MMMMMMMMMMMMMMMM" -- M x 16 (SCE_NP_ONLINEID_MAX_LENGTH)

dofile("/app0/game_data/resources.lua")

-- Adjust the sensitivity of play style
config.play_style_sensitivity["left_stick_movable_viewpoint"]		= 0.01
config.play_style_sensitivity["motion_sensor_movable_viewpoint"]		= 0.75
config.play_style_sensitivity["motion_sensor_fixed_viewpoint"]			= 0.5
config.play_style_sensitivity["touch_pad_movable_viewpoint"]		= 0.6
config.play_style_sensitivity["touch_pad_fixed_viewpoint"]			= 1.0
config.play_style_sensitivity["pad_tracker_fixed_viewpoint"]    = 1.0
