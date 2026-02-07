
config.useArchive = true
if config.useArchive then
   modeldir = config.mount_point .. "model/"
   sounddir = config.mount_point .. "sound/"
   imagedir = config.mount_point .. "image/"
else
   modeldir = "/app0/game_data/model/"
   sounddir = "/app0/game_data/sound/"
   imagedir = "/app0/game_data/image/"
end

config.livearea_data_dir = "/app0/game_data/livearea_data"

-- File paths of model.
config.model_path["gun"]						= modeldir .. "gun/obj_gun_snipe.dae"
config.model_path["target_a"]					= modeldir .. "target/obj_target_a.dae"
config.model_path["shooting_range"]             = modeldir .. "shooting_range/shooting_range.dae"
config.model_path["bullet"]						= modeldir .. "duck/duck.dae"

-- File paths of textures
config.texture_path["title_bg"]					= imagedir .. "title_background.tga"
config.texture_path["busy48"]					= imagedir .. "busy48.png"
config.texture_path["eff_explode"]				= imagedir .. "eff_explode.tga"
config.texture_path["eff_shot"]				    = imagedir .. "eff_shot.tga"
config.texture_path["bullet"]				    = imagedir .. "bullet.png"
config.texture_path["target_g"]					= modeldir .. "target/texture/tx_target_g.tga"
config.texture_path["verified_account_icon_large"]    = imagedir .. "verified_account_icon_large.png"
config.texture_path["verified_account_icon_small"]    = imagedir .. "verified_account_icon_small.png"

-- File paths of sound
config.sound_path["shot"]          = sounddir .. "cannon_mono.at9"
config.sound_path["explosion"]     = sounddir .. "explode.at9"
config.sound_path["reload"]        = sounddir .. "reload.at9"
config.sound_path["game_bgm"]      = sounddir .. "bgm_loop.at9"
config.sound_path["applause"]      = "/app0/game_data/sound/applause.wav"

-- Text Table

config.text_table_ucs2 = 
	{	
      	LOADING = 
		{
			english_us = "Loading ...",
			japanese   = "ロード中..."
		},

      	SAVING = 
		{
			english_us = "Now saving...",
			japanese   = "セーブ中..."
		},

      	PUSH_X_BUTTON = 
		{
			english_us = "Push × button",
			japanese   = "×ボタンを押してください"
		},

		SINGLE_PLAYER_RECORD_SCENE_SYSTEM_MESSAGE = 
		{
			english_us = "△ button : Online Ranking   × button : Top Menu",
			japanese   = "△ボタン : オンラインランキング   ×ボタン : トップメニュー"
		},

		ONLINE_WAITING_FOR_OTHER_USERS = 
		{
			english_us = "waiting for other users starting...",
			japanese   = "他のユーザのスタートを待っています..."
		},

		ONLINE_BEFORE_STARTING_GAME = 
		{
			english_us = "When the number of users is 2 or more, you can start game",
			japanese   = "ユーザが2人以上のときゲームを開始することができます"
		},

		ONLINE_UNAVAILABLE_PS_PLUS = 
		{
			english_us = "You don't have PlayStationⓇPlus",
			japanese   = "あなたはPlayStationⓇPlus会員ではありません"
		},

		ONLINE_NETWORK_ERROR = 
		{
			english_us = "network error occured",
			japanese   = "ネットワークエラーが起きました"
		},

		ONLINE_ROOM_SCENE_CIRCLE_BUTTON_BEHAVIOR_SERVER = 
		{
			english_us = "○ button : Destroy Room",
			japanese   = "○ボタン : ルームを破棄する"
		},

		ONLINE_ROOM_SCENE_CROSS_BUTTON_BEHAVIOR_SERVER = 
		{
			english_us = "× button : Start Match",
			japanese   = "×ボタン : ゲームを開始する"
		},

		ONLINE_ROOM_SCENE_CIRCLE_BUTTON_BEHAVIOR_CLIENT = 
		{
			english_us = "○ button : Leave Room",
			japanese   = "○ボタン : ルームから退出する"
		},

		ONLINE_ROOM_SCENE_CROSS_BUTTON_BEHAVIOR_CLIENT = 
		{
			english_us = "× button : Get Ready to Match",
			japanese   = "×ボタン : 対戦への参加を表明する"
		},

		ONLINE_ROOM_SCENE_CONNECTING_TO_OWNER = 
		{
			english_us = "Connecting...",
			japanese   = "接続中..."
		},

		ONLINE_ROOM_SCENE_WAITING_OWNER_TO_START_MATCH = 
		{
			english_us = "Waiting for the Owner to Start Match...",
			japanese   = "オーナーが対戦を開始するのを待っています..."
		},

		ONLINE_MATCH_AUDIENCE_MODE_MESSAGE = 
		{
			english_us = "Watching other users match",
			japanese   = "他のユーザの対戦を観戦中です"
		},

		PLAY_STYLE_MOTION_MOVABLE_VIEWPOINT_DISABLE_MESSAGE =
		{
			english_us = "Additional Content is not available",
			japanese   = "追加コンテンツがありません"
		},

		PLAY_STYLE_PAD_TRACKER_FIXED_VIEWPOINT_DISABLE_MESSAGE_FOR_NOT_AVAILABLE_FOR_REMOTE_PLAY =
		{
			english_us = "Pad Tracker is not available for Remote Play",
			japanese   = "リモートプレイでパッドトラッカーを使用することはできません"
		},

		PLAY_STYLE_PAD_TRACKER_FIXED_VIEWPOINT_DISABLE_MESSAGE_FOR_NOT_SELECTABLE_WHILE_GAME =
		{
			english_us = "Pad Tracker is not selectable while\nplaying game",
			japanese   = "対戦中にパッドトラッカーを選択することはできません"
		},

		PLAY_STYLE_PAD_TRACKER_FIXED_VIEWPOINT_DISABLE_MESSAGE_FOR_CAMERA_DISCONNECT =
		{
			english_us = "PlayStationⓇCamera is not connected.",
			japanese   = "PlayStationⓇCameraが接続されていません"
		},

		PROMOTE_MESSAGE_FOR_CHANGE_TO_DS4_FROM_REMOTE_PLAY =
		{
			english_us = "Press the PS button on the DUALSHOCK®4 wireless controller and log in again",
			japanese   = "ワイヤレスコントローラー(DUALSHOCK®4)のPSボタンを押し、ログインし直して下さい"
		},

		CAMERA_DISCONNECT_MESSAGE =
		{
			english_us = "PlayStationⓇCamera is disconnected!!",
			japanese   = "PlayStationⓇCameraが接続されていません!!"
		},

		WAITING_FOR_OTHER_USERS =
		{
			english_us = "Waiting for other users...",
			japanese   = "他のユーザを待っています..."
		},

		READY =
		{
			english_us = "READY",
			japanese   = "レディー"
		},

		TIME_UP =
		{
			english_us = "TIME UP",
			japanese   = "タイムアップ"
		},

		RANKING =
		{
			english_us = "RANKING",
			japanese   = "ランキング"
		},

		PLEASE_LOGIN =
		{
			english_us = "Please Login!",
			japanese   = "ログインしてください!"
		},

		PLEASE_JOIN =
		{
			english_us = "Please Join!",
			japanese   = "参加してください!"
		},

		GAME_MASTER =
		{
			english_us = "Game Master",
			japanese   = "ゲームマスター"
		},

		PAD_TRACKER_NOT_TRACKING_MESSAGE =
		{
			english_us = "PlayStationⓇCamera is not tracking light bar",
			japanese   = "カメラがライトバーを検出していません"
		},

		PAD_TRACKER_ROOM_CONFLICT_MESSAGE =
		{
			english_us = "Room conflict is occurring",
			japanese   = "画像内にライトバーと同じ色の物体があります"
		},

		PAD_TRACKER_CALIBRATING_MESSAGE =
		{
			english_us = "PlayStationⓇCamera is calibrating...",
			japanese   = "キャリブレーション中..."
		},

		PAD_TRACKER_ERROR_MESSAGE =
		{
			english_us = "An error is occurring",
			japanese   = "エラーが起きました"
		},

		PAD_TRACKER_SETTING_MESSAGE_FOR_OPERATION_RANGE_DEFINITION =
		{
			english_us = "Press R2 button 10 times to define your operation range",
			japanese   = "R2ボタンを10回押して、操作範囲を決定してください"
		},

		PAD_TRACKER_SETTING_MESSAGE_FOR_SINGLE_PLAY_OPERATION_RANGE =
		{
			english_us = "Your operation range is being indicated with your color rectangle",
			japanese   = "操作範囲がユーザカラーの長方形で示されています"
		},

		PAD_TRACKER_SETTING_MESSAGE_FOR_MULTI_PLAY_OPERATION_RANGES =
		{
			english_us = "The operation ranges are being indicated with each player color rectangle",
			japanese   = "操作範囲がユーザカラーの長方形で示されています"
		},

		PAD_TRACKER_SETTING_MESSAGE_FOR_GAME_START =
		{
			english_us = "Push × button to start the game",
			japanese   = "×ボタンを押してゲームを開始します"
		},

		VIDEO_RECORDING_NO_SPACE_ERROR_NOTIFICATION =
		{
			english_us = "Failed to record game video",
			japanese   = "ゲームの録画に失敗しました"
		},

		X_BUTTON_TO_HIGH_SCORE = 
		{
			english_us = "× button : High Score",
			japanese   = "×ボタン : ハイスコア"
		},		
	}

config.text_table_utf8 = 
	{
		SINGLE_PLAYER_SAVE_DATA_TITLE =
		{
			english_us = "Single user mode high score data",
			japanese   = "シングルユーザーモードのハイスコアデータ"
		},

		SINGLE_PLAYER_SAVE_DATA_SUB_TITLE =
		{
			english_us = "SIMPLE SHOOTING GAME",
			japanese   = "シンプルシューティングゲーム"
		},
	
		SINGLE_PLAYER_SAVE_DATA_DETAIL =
		{
			english_us = "The high score of single user mode is recorded",
			japanese   = "シングルユーザーモードのハイスコアデータが記録されています"
		},

		MULTI_PLAYER_SAVE_DATA_TITLE =
		{
			english_us = "Multi user mode winning points data",
			japanese   = "マルチユーザーモードの勝ち点データ"
		},

		MULTI_PLAYER_SAVE_DATA_SUB_TITLE =
		{
			english_us = "SIMPLE SHOOTING GAME",
			japanese   = "シンプルシューティングゲーム"
		},
	
		MULTI_PLAYER_SAVE_DATA_DETAIL =
		{
			english_us = "The winning points data of multi user mode is recorded",
			japanese   = "マルチユーザーモードの勝ち点データが記録されています"
		},

		PLAY_STYLE_0_NAME =
		{
			english_us = "Left Stick - Movable Viewpoint",
			japanese   = "左スティック(視点移動)"
		},

		PLAY_STYLE_1_NAME =
		{
			english_us = "Touch Pad - Movable Viewpoint",
			japanese   = "タッチパッド(視点移動)"
		},

		PLAY_STYLE_2_NAME =
		{
			english_us = "Touch Pad - Fixed Viewpoint",
			japanese   = "タッチパッド(視点固定)"
		},

		PLAY_STYLE_3_NAME =
		{
			english_us = "Motion Sensor - Movable Viewpoint",
			japanese   = "モーションセンサー(視点移動)"
		},

		PLAY_STYLE_4_NAME =
		{
			english_us = "Motion Sensor - Fixed Viewpoint",
			japanese   = "モーションセンサー(視点固定)"
		},

		PLAY_STYLE_5_NAME =
		{
			english_us = "Pad Tracker - Fixed Viewpoint",
			japanese   = "パッドトラッカー(視点固定)"
		},

		CHEERING =
		{
			english_us = "Cheering!",
			japanese   = "応援中!"
		},

		PLEASE_CHEER =
		{
			english_us = "Please Cheer!",
			japanese   = "応援してください!"
		},

		CHEERED_COUNT =
		{
			english_us = "Cheered Count:",
			japanese   = "応援カウント:"
		},

		ONLINE_RANKING_RECORDING_SCORE_AND_GETTING_RANKING = 
		{
			english_us = "recording your score and getting the ranking...",
			japanese   = "スコア登録およびランキング取得中です..."
		},

		-- Not displaying messages related to PlayStationⓇPlus before the call of sceNpCommerceDialogOpen()
		ONLINE_CHECKING_PS_PLUS = 
		{
			english_us = "Connecting to the network...",
			japanese   = "ネットワークに接続中..."
		},

		ONLINE_CHECKING_AVAILABILITY = 
		{
			english_us = "Confirming the network setting...",
			japanese   = "ネットワーク設定を確認中..."
		},

      	ONLINE_MSG_DIALOG_SIGNOUT = 
		{
			english_us = "Sign-out from PSN℠ occurs.\nFollowing features become unusable.\n  - Network Matching\n  - Online Ranking\n",
			japanese   = "PSN℠からのサインアウトが発生しました。\n以下の機能が利用できません。\n  ・ネットワーク対戦\n  ・オンラインランキング\n"
		},

      	ONLINE_MSG_DIALOG_SCE_TOOLKIT_NP_ERROR_MATCHING_SESSION_ROOM_DESTROYED = 
		{
			english_us = "A network error has occurred.\n\n  - The network might be disconnected.\n  - When you were not the owner of the room, the room might have been destroyed\n    because the owner left the room.\n\nConfirm the network connection, then search rooms again or create another room.",
			japanese   = "通信エラーが発生しました。\n\n  ・ネットワークが切断された可能性があります。\n  ・あなたがルームのオーナーではなかった場合、オーナーがルームから退室したことによりルームがなくなった可能性があります。\n\nネットワークの状況を確認し、再度ルームを検索するか、ルームを作成してください。\n"
		},

      	ONLINE_MSG_DIALOG_RUDP_CONNECTION_LOST = 
		{
			english_us = "The network connection to the owner is lost.\n",
			japanese   = "オーナーとのネットワーク接続が失われました。\n"
		},

      	ONLINE_MSG_DIALOG_DISABLE_TO_INVITE_BECAUSE_ROOM_IS_FULL = 
		{
			english_us = "You can't send an invitation because the room is full.\n",
			japanese   = "ルームが定員に達しているため、招待を送ることができません。\n"
		},

		ONLINE_CREATING_ROOM = 
		{
			english_us = "creating room...",
			japanese   = "ルームを作成しています..."
		},

		ONLINE_SEARCHING_ROOMS = 
		{
			english_us = "searching rooms...",
			japanese   = "ルームを検索しています..."
		},

		ONLINE_ENTERING_ROOM = 
		{
			english_us = "entering room...",
			japanese   = "ルームに入室しています..."
		},

		ONLINE_LEAVING_ROOM = 
		{
			english_us = "leaving room...",
			japanese   = "ルームから退出しています..."
		},

		ONLINE_NO_ROOM_FOUND = 
		{
			english_us = "No room was found.",
			japanese   = "ルームが見つかりませんでした。"
		},

		ONLINE_QUITTING_MATCH_SERVER = 
		{
			english_us = "Quit match and return to room.",
			japanese   = "対戦を中止してルームに戻ります。"
		},

		ONLINE_QUITTING_MATCH_CLIENT_PLAYER_MODE= 
		{
			english_us = "Quit match and leave room.",
			japanese   = "対戦を中止してルームから退出します。"
		},

		ONLINE_QUITTING_MATCH_CLIENT_AUDIENCE_MODE= 
		{
			english_us = "Quit watching match and leave room.",
			japanese   = "観戦を中止してルームから退出します。"
		},

		INVITATION_INVITE_MESSAGE = 
		{
			english_us = "Let's play Online Match!",
			japanese   = "オンライン対戦しよう！"
		},

      	MSG_DIALOG_FAILED_TO_RECORD_VIDEO_NO_SPACE = 
		{
			english_us = "Failed to record game video due to insufficient free space.\n",
			japanese   = "空き容量不足によりゲームプレイを録画できませんでした。\n"
		},

      	MSG_DIALOG_MOVIE_FILE_NOT_EXIST = 
		{
			english_us = "The movie file of the game does not exist.\n",
			japanese   = "ゲームの動画ファイルがありません。\n"
		},

      	MSG_DIALOG_USER_LOGOUT = 
		{
			english_us = "The user logged out.\n",
			japanese   = "ユーザはログアウトしました。\n"
		},

      	MSG_DIALOG_DELETE_BROKEN_SAVE_DATA_AND_CREATE_NEW_SAVE_DATA_SINGLE = 
		{
			english_us = "The save data is corrupted.\nDelete the data, and create a new save data",
			japanese   = "セーブデータが壊れています。\n壊れたセーブデータを削除し、新しいセーブデータを作成します。\n"
		},

      	MSG_DIALOG_DELETE_BROKEN_SAVE_DATA_AND_CREATE_NEW_SAVE_DATA_MULTI = 
		{
			english_us = "The following user's save data is corrupted.\nDelete the data, and create a new save data\n\nUser Name : ",
			japanese   = "以下のユーザのセーブデータが壊れています。\n壊れたセーブデータを削除し、新しいセーブデータを作成します。\n\nユーザ名 : "
		},

		SELECTING_PLAYSTYLE =
		{
			english_us = "Selecting playstyle...",
			japanese   = "プレイスタイル選択中..."
		},
	}

function chooseText(lang, etext, jtext)
	if lang	== "japanese" then
        return jtext
    else
        return etext
    end
end

function textBox(id, pos, size, weight, color, align, text)
   ret = "    <textbox id='" .. id ..  "' x=" .. tostring(pos[1]) .. " y=" .. tostring(pos[2]) .. " width=" .. tostring(size[1]) .. " height=" .. tostring(size[2]) .. 
	  "  fontweight=" .. weight .. " color='" .. color .. "' align=".. align.. ">\n" .. text .. "</textbox>\n"
   return  ret
end

function simpleImage(id, pos, size)
   ret = "    <image id='" .. id ..  "' x=" .. tostring(pos[1]) .. " y=" .. tostring(pos[2]) .. " width=" .. tostring(size[1]) .. " height=" .. tostring(size[2])  .. "></image>\n"
   --- print(ret)
   return  ret
end

function anim(animationtime, easein, easeout)
   return { animationtime=animationtime, easein=easein, easeout=easeout }
end

function textpos(pos, hidePos, size, align)
   return { pos=pos, hidePos=hidePos, size=size, align=align }
end

function textBoxDetail(id, textpos, anim, weight, color, text, cursorIndex, lines)
   ret = "    <textbox id='" .. id ..  "' x=" .. tostring(textpos.pos[1]) .. " y=" .. tostring(textpos.pos[2]) .. 
	  " hidex=" .. tostring(textpos.hidePos[1]) .. " hidey=" .. tostring(textpos.hidePos[2]) ..
	  " width=" ..	tostring(textpos.size[1]) .. " height="	.. tostring(textpos.size[2]) ..
	  " animationtime=" ..	tostring(anim["animationtime"]) .. " easein="	.. tostring(anim["easein"]) .. " easeout="	.. tostring(anim["easeout"]) ..
	  "  fontweight=" .. weight .. " color='" .. color .. "' align=".. textpos.align.. " cursor_index_x=" .. cursorIndex[1] .. " cursor_index_y=" .. cursorIndex[2] .. 
	  " lines=" .. tostring(lines) .. ">\n" 
	  .. text .. "</textbox>\n"
   return  ret
end
    
ps = {}
ps[0] = config.text_table_utf8["PLAY_STYLE_0_NAME"][language]
ps[1] = config.text_table_utf8["PLAY_STYLE_1_NAME"][language]
ps[2] = config.text_table_utf8["PLAY_STYLE_2_NAME"][language]
ps[3] = config.text_table_utf8["PLAY_STYLE_3_NAME"][language]
ps[4] = config.text_table_utf8["PLAY_STYLE_4_NAME"][language]
ps[5] = config.text_table_utf8["PLAY_STYLE_5_NAME"][language]

-------------------------------------------


function playstyle_menu_item(psindex, menuindex, offset_y)
   return 	  textBox("ps" .. tostring(psindex) .. "name",   { 0.02, 0.3+0.08*menuindex + offset_y }, { 0.52, 0.05 }, "bold",   "#ffffffff", "left", ps[psindex]) ..
	  textBoxDetail("ps" .. tostring(psindex) .. "extmsg", textpos({0.55, 0.31+0.08*menuindex + offset_y}, {0.55, 0.31+0.08*menuindex + offset_y}, {0.45, 0.06}, "left"), anim(0.0, "cubicin", "cubicout"), "normal", "#c0c0ffff", "", {-1,-1}, 2)
end

function playstyle_menu(offset_y)
	if ispatched then
		return playstyle_menu_item(0, 0, offset_y) ..
			playstyle_menu_item(1, 1, offset_y) ..
			playstyle_menu_item(2, 2, offset_y) ..
			playstyle_menu_item(3, 3, offset_y) ..
			playstyle_menu_item(4, 4, offset_y) ..
			playstyle_menu_item(5, 5, offset_y) 
	else
		return playstyle_menu_item(0, 0, offset_y) ..
			playstyle_menu_item(1, 1, offset_y) ..
			playstyle_menu_item(2, 2, offset_y) ..
			playstyle_menu_item(4, 3, offset_y) ..
			playstyle_menu_item(5, 4, offset_y) 
	end
end

-------------------------------------------

function get_single_play_high_score_item(psindex, menuindex)
   return 
	  textBox("ps" .. tostring(psindex) .. "name",   { 0.02, 0.3+0.08*menuindex},   { 0.5, 0.05 },  "bold",   "#ffffffff", "left", ps[psindex]) ..
	  textBox("ps" .. tostring(psindex) .. "_r1",    { 0.55, 0.3+0.08*menuindex},   { 0.10, 0.05 }, "normal", "#ffffffff", "right", "") ..
	  textBox("ps" .. tostring(psindex) .. "_r2",    { 0.67, 0.3+0.08*menuindex},   { 0.10, 0.05 }, "normal", "#ffffffff", "right", "") ..
	  textBox("ps" .. tostring(psindex) .. "_r3",    { 0.79, 0.3+0.08*menuindex},   { 0.10, 0.05 }, "normal", "#ffffffff", "right", "")
end

if ispatched then
   single_play_high_scores = 
        get_single_play_high_score_item(0, 0) ..
        get_single_play_high_score_item(1, 1) ..
        get_single_play_high_score_item(2, 2) ..
        get_single_play_high_score_item(3, 3) ..
        get_single_play_high_score_item(4, 4) ..
        get_single_play_high_score_item(5, 5) 
else
   single_play_high_scores = 
        get_single_play_high_score_item(0, 0) ..
        get_single_play_high_score_item(1, 1) ..
        get_single_play_high_score_item(2, 2) ..
        get_single_play_high_score_item(4, 3) ..
        get_single_play_high_score_item(5, 4) 
end

function user_profile_contents(id, pos, size, weight, color, align, text)
   return 
	  textBox(id, pos, size, weight, color, align, text) ..
	  simpleImage(id .. "_verified_account_icon", pos, { 0.0, 0.0 })
end

single_play_high_score_scene_template = 
		"<window>\n" ..
		"	<image id=bg/>" ..
		"	<widget id=safe_area>" ..
			textBox("",          { 0.004, 0.02}, { 0.5, 0.1  }, "bold",   "#ffffffff", "left", chooseText(language, "High Score", "ハイスコア")) ..
			user_profile_contents("userName", {0.004,	0.13}, {0.5, 0.07},	"bold",	 "#ffffffff", "left", "userName")..
			textBox("rank1",     { 0.55, 0.3-0.08*1},  { 0.10, 0.05 }, "bold",   "#ffffffff", "right", "1st") ..
			textBox("rank2",     { 0.67, 0.3-0.08*1},  { 0.10, 0.05 }, "bold",   "#ffffffff", "right", "2nd") ..
			textBox("rank3",     { 0.79, 0.3-0.08*1},  { 0.10, 0.05 }, "bold",   "#ffffffff", "right", "3rd") ..

			single_play_high_scores ..
		"	</widget>" ..
		"</window>\n"

-------------------------------------------

function bulletRemains(playerIndex,	pos)
   ystep = 0.03
   size = { 0.05, 0.028 } 
   return
      simpleImage("bulletRemain" .. tostring(playerIndex) .. "_0", {pos[1],	pos[2] + ystep*0}, size)..
      simpleImage("bulletRemain" .. tostring(playerIndex) .. "_1", {pos[1],	pos[2] + ystep*1}, size)..
      simpleImage("bulletRemain" .. tostring(playerIndex) .. "_2", {pos[1],	pos[2] + ystep*2}, size)..
      simpleImage("bulletRemain" .. tostring(playerIndex) .. "_3", {pos[1],	pos[2] + ystep*3}, size)..
      simpleImage("bulletRemain" .. tostring(playerIndex) .. "_4", {pos[1],	pos[2] + ystep*4}, size)..
      simpleImage("bulletRemain" .. tostring(playerIndex) .. "_5", {pos[1],	pos[2] + ystep*5}, size)
end

function get_multi_play_record_scene_player(userIndex)
    step = 0.09
  	scoreX = 0.75
    if ispatched then
        return user_profile_contents("user" .. tostring(userIndex), {0.0, 0.0}, {1.0, 0.1},	"bold",	 "#ffffffff", "left", "")..
               textBox("ps0name",	 { 0.00, 0.15+step*0},	{ scoreX, step-0.01	},	"bold",	  "#ffffffff", "left", ps[0])	..
               textBox("ps1name",	 { 0.00, 0.15+step*1},	{ scoreX, step-0.01	},	"bold",	  "#ffffffff", "left", ps[1])	..
               textBox("ps2name",	 { 0.00, 0.15+step*2},	{ scoreX, step-0.01	},	"bold",	  "#ffffffff", "left", ps[2])	..
               textBox("ps3name",	 { 0.00, 0.15+step*3},	{ scoreX, step-0.01	},	"bold",	  "#ffffffff", "left", ps[3])	..
               textBox("ps4name",	 { 0.00, 0.15+step*4},	{ scoreX, step-0.01	},	"bold",	  "#ffffffff", "left", ps[4])	..
               textBox("ps5name",	 { 0.00, 0.15+step*5},	{ scoreX, step-0.01	},	"bold",	  "#ffffffff", "left", ps[5])	..
			   textBox("ps0_u" .. tostring(userIndex),	 {	scoreX, 0.15+step*0},	 { 0.10, step-0.01 }, "normal", "#ffffffff",	"right", "") ..
			   textBox("ps1_u" .. tostring(userIndex),	 {	scoreX, 0.15+step*1},	 { 0.10, step-0.01 }, "normal", "#ffffffff",	"right", "") ..
			   textBox("ps2_u" .. tostring(userIndex),	 {	scoreX, 0.15+step*2},	 { 0.10, step-0.01 }, "normal", "#ffffffff",	"right", "") ..
			   textBox("ps3_u" .. tostring(userIndex),	 {	scoreX, 0.15+step*3},	 { 0.10, step-0.01 }, "normal", "#ffffffff",	"right", "") ..
			   textBox("ps4_u" .. tostring(userIndex),	 {	scoreX, 0.15+step*4},	 { 0.10, step-0.01 }, "normal", "#ffffffff",	"right", "") ..
			   textBox("ps5_u" .. tostring(userIndex),	 {	scoreX, 0.15+step*5},	 { 0.10, step-0.01 }, "normal", "#ffffffff",	"right", "") 
    else
        return user_profile_contents("user" .. tostring(userIndex), {0.0, 0.0}, {1.0, 0.1},	"bold",	 "#ffffffff", "left", "")..
               textBox("ps0name",	 { 0.00, 0.15+step*0},	{ scoreX, step-0.01	},	"bold",	  "#ffffffff", "left", ps[0])	..
               textBox("ps1name",	 { 0.00, 0.15+step*1},	{ scoreX, step-0.01	},	"bold",	  "#ffffffff", "left", ps[1])	..
               textBox("ps2name",	 { 0.00, 0.15+step*2},	{ scoreX, step-0.01	},	"bold",	  "#ffffffff", "left", ps[2])	..
               textBox("ps4name",	 { 0.00, 0.15+step*3},	{ scoreX, step-0.01	},	"bold",	  "#ffffffff", "left", ps[4])	..
               textBox("ps5name",	 { 0.00, 0.15+step*4},	{ scoreX, step-0.01	},	"bold",	  "#ffffffff", "left", ps[5])	..
			   textBox("ps0_u" .. tostring(userIndex),	 {	scoreX, 0.15+step*0},	 { 0.10, step-0.01 }, "normal", "#ffffffff",	"right", "") ..
			   textBox("ps1_u" .. tostring(userIndex),	 {	scoreX, 0.15+step*1},	 { 0.10, step-0.01 }, "normal", "#ffffffff",	"right", "") ..
			   textBox("ps2_u" .. tostring(userIndex),	 {	scoreX, 0.15+step*2},	 { 0.10, step-0.01 }, "normal", "#ffffffff",	"right", "") ..
			   textBox("ps4_u" .. tostring(userIndex),	 {	scoreX, 0.15+step*3},	 { 0.10, step-0.01 }, "normal", "#ffffffff",	"right", "") ..
			   textBox("ps5_u" .. tostring(userIndex),	 {	scoreX, 0.15+step*4},	 { 0.10, step-0.01 }, "normal", "#ffffffff",	"right", "") 
    end
 end


multi_play_record_scene_template2 = 
	"<window>\n" ..
	"	<image id=bg/>" ..
	"	<widget id=safe_area>" ..   
		textBox("",          { 0.004, 0.02}, { 0.5, 0.1  }, "bold",   "#ffffffff", "left", chooseText(language, "Record", "レコード")) ..
        "<widget id=w0 x=0.05 y=0.2 width=0.45 height=0.40 hidex=100>" ..
            get_multi_play_record_scene_player(0) ..
        "</widget>" ..
        "<widget id=w1 x=0.5 y=0.2 width=0.45 height=0.40 hidex=100>" ..
            get_multi_play_record_scene_player(1) ..
        "</widget>" ..
        "<widget id=w2 x=0.05 y=0.6 width=0.45 height=0.40 hidex=100>" ..
            get_multi_play_record_scene_player(2) ..
        "</widget>"..
        "<widget id=w3 x=0.5 y=0.6 width=0.45 height=0.40 hidex=100>" ..
            get_multi_play_record_scene_player(3) ..
        "</widget>" ..
	"	</widget>" ..
	"</window>\n"


-----------------------------------------------------------

config.scene_template_table = 
	{
		SINGLE_USER_TITLE_SCENE = 
		"<window>\n" ..
		"	<image id=bg/>" ..
		"	<widget id=safe_area>" ..
		"		<textbox id='title1sdw' x=0.004 y=0.174 hidey=-0.226 animationtime=0.5 easein=cubicin width=1.0 height=0.15 fontweight=bold color='#4c4c4cb3' align=center>\n" ..
				chooseText(language, "SINGLE USER", "シングルユーザー") ..
		"		</textbox>" ..			 
		"		<textbox id='title1'    x=0.0   y=0.17  hidey=-0.230 animationtime=0.5 easein=cubicin width=1.0 height=0.15 fontweight=bold color='#ff0000ff' align=center>\n" ..
				chooseText(language, "SINGLE USER", "シングルユーザー") ..
		"		</textbox>" ..			 
		"		<textbox id='title2sdw' x=0.004 y=0.374 hidey=-0.026 animationtime=0.5 easein=cubicin width=1.0 height=0.15 fontweight=bold color='#4c4c4cb3' align=center>\n" ..
				chooseText(language, "SHOOTING GAME",	"シューティングゲーム")	..
		"		</textbox>" ..			 
		"		<textbox id='title2'    x=0.0   y=0.37  hidey=-0.030 animationtime=0.5 easein=cubicin width=1.0 height=0.15 fontweight=bold color='#ff0000ff' align=center>\n" ..
				chooseText(language, "SHOOTING GAME",	"シューティングゲーム")	..
		"		</textbox>" ..			 
				textBoxDetail("menu_game_start", textpos({0.3, 0.55}, {0.3, 0.85}, {0.4,0.08}, "center"), anim(0.5, "cubicin", "cubicout"), "bold", "#ffffffff", chooseText(language, "Game Start", "ゲームスタート"), {0,0}, 1) ..
				textBoxDetail("menu_high_score", textpos({0.3, 0.65}, {0.3, 0.95}, {0.4,0.08}, "center"), anim(0.5, "cubicin", "cubicout"), "bold", "#ffffffff", chooseText(language, "High Score", "ハイスコア"),     {0,1}, 1) ..
				textBoxDetail("menu_multi_play", textpos({0.3, 0.75}, {0.3, 1.05},{0.4,0.08}, "center"), anim(0.5, "cubicin", "cubicout"), "bold", "#ffffffff", chooseText(language, "Multi Play", "マルチプレイ"),   {0,2}, 1) ..
				textBoxDetail("menu_replay",     textpos({0.3, 0.85}, {0.3, 1.15},{0.4,0.08}, "center"), anim(0.5, "cubicin", "cubicout"), "bold", "#ffffffff", chooseText(language, "Replay",     "リプレイ"),       {0,3}, 1) ..
		"	</widget>" ..
		"</window>\n",

		MULTI_USER_TITLE_SCENE = 
		"<window>\n" ..
		"	<image id=bg/>" ..
		"	<widget id=safe_area>" ..
		"		<textbox id='title1sdw' x=0.004 y=0.174 hidey=-0.226 animationtime=0.5 easein=cubicin width=1.0 height=0.15 fontweight=bold color='#4c4c4cb3' align=center>\n" ..
				chooseText(language, "MULTI USER", "マルチユーザー") ..
		"		</textbox>" ..			 
		"		<textbox id='title1'    x=0.0   y=0.17  hidey=-0.230 animationtime=0.5 easein=cubicin width=1.0 height=0.15 fontweight=bold color='#ff0000ff' align=center>\n" ..
				chooseText(language, "MULTI USER", "マルチユーザー") ..
		"		</textbox>" ..			 
		"		<textbox id='title2sdw' x=0.004 y=0.374 hidey=-0.026 animationtime=0.5 easein=cubicin width=1.0 height=0.15 fontweight=bold color='#4c4c4cb3' align=center>\n" ..
				chooseText(language, "SHOOTING GAME",	"シューティングゲーム")	..
		"		</textbox>" ..			 
		"		<textbox id='title2'    x=0.0   y=0.37  hidey=-0.030 animationtime=0.5 easein=cubicin width=1.0 height=0.15 fontweight=bold color='#ff0000ff' align=center>\n" ..
				chooseText(language, "SHOOTING GAME",	"シューティングゲーム")	..
		"		</textbox>" ..			 

				textBoxDetail("menu_game_start",   textpos({0.3, 0.55+0.08*0}, {0.3, 0.85+0.08*0}, {0.4,0.07}, "center"), anim(0.5, "cubicin", "cubicout"), "bold", "#ffffffff", chooseText(language, "Game Start",   "ゲームスタート"),   {0,0}, 1) ..
				textBoxDetail("menu_record",       textpos({0.3, 0.55+0.08*1}, {0.3, 0.85+0.08*1}, {0.4,0.07}, "center"), anim(0.5, "cubicin", "cubicout"), "bold", "#ffffffff", chooseText(language, "Record",	     "レコード"),         {0,1}, 1) ..
				textBoxDetail("menu_single_play",  textpos({0.3, 0.55+0.08*2}, {0.3, 0.85+0.08*2}, {0.4,0.07}, "center"), anim(0.5, "cubicin", "cubicout"), "bold", "#ffffffff", chooseText(language, "Single Play",  "シングルプレイ"),   {0,2}, 1) ..
				textBoxDetail("menu_replay",	    textpos({0.3, 0.55+0.08*3}, {0.3, 0.85+0.08*3}, {0.4,0.07}, "center"), anim(0.5, "cubicin", "cubicout"), "bold", "#ffffffff", chooseText(language, "Replay",	     "リプレイ"),		  {0,3}, 1) ..
				textBoxDetail("menu_online_match", textpos({0.3, 0.55+0.08*4}, {0.3, 0.85+0.08*4}, {0.4,0.07}, "center"), anim(0.5, "cubicin", "cubicout"), "bold", "#ffffffff", chooseText(language, "Online Match", "オンラインマッチ"), {0,4}, 1) ..
		"	</widget>" ..
		"</window>\n",

		TOP_LEVEL_HUD = 
		"<window>\n" ..
		"	<widget id=safe_area>" ..
		"		<textbox id='system_message' x=0.0 y=0.95 hidey=1.0 animationtime=0.5 easein=cubicin width=1.0 height=0.05 fontweight=bold color='#ffffffff' align=right>\n" ..
		"		</textbox>" ..			 
		"	</widget>" ..
		"</window>\n",

		PLAY_STYLE_MENU_SCENE_FOR_MULTI_USER = 
		"<window>\n" ..
		"	<image id=bg/>" ..
		"	<widget id=safe_area>" ..
		"		<widget id=''    x=0.24   y=0.32.5 width=0.52 height=0.35 bgcolor='#dfdfdfff'>\n" ..
				textBox("countdown", {0.0, 0.03}, {1.0, 0.15}, "bold",   "#ff0000ff", "center", chooseText(language, "10", "10"))..
				textBox("",          {0.0, 0.21}, {1.0, 0.12}, "bold",   "#000000ff", "center", chooseText(language, "Play Style Setting", "プレイスタイル設定")) ..
				textBox("",          {0.0, 0.36}, {1.0, 0.12}, "normal", "#000000ff", "center", chooseText(language, "× button : Enter　○ button :  Back", "×ボタン : 決定　○ボタン : 戻る")) ..
				textBox("",          {0.0, 0.54}, {1.0, 0.10}, "bold",   "#000000ff", "center", chooseText(language, "What to do to play becoming", "ゲームマスターになって")) ..
				textBox("",          {0.0, 0.64}, {1.0, 0.10}, "bold",   "#000000ff", "center", chooseText(language, "the GameMaster and placing targets?",	"ターゲットを配置して遊ぶには？"))	..
				textBox("",          {0.0, 0.77}, {1.0, 0.10}, "normal", "#000000ff", "center", chooseText(language, "Connect PS4 Link or PlayStationⓇApp to",	"PS4リンク、またはPlayStationⓇAppをPlayStationⓇ4に"))	..
				textBox("",          {0.0, 0.87}, {1.0, 0.10}, "normal", "#000000ff", "center", chooseText(language, "PlayStationⓇ4 and display the Second Screen.",	"接続してセカンドスクリーンを表示してください。"))	..
		"		</widget>" ..			 
        "	</widget>" ..			 
		"</window>\n",

		PLAY_STYLE_MENU_SCENE_FOR_ONLINE = 
		"<window>\n" ..
		"	<image id=bg/>" ..
		"	<widget id=safe_area>" ..
		"		<textbox id='playstyle' x=0.004 y=0.18 width=0.5 height=0.09 fontweight=bold color='#ffffffff' align=left>\n" ..
					 chooseText(language, "Play Style", "プレイスタイル") ..
		"		</textbox>" ..			 
		"		<textbox id='' x=0.000 y=0.76 width=1.0 height=0.07 fontweight=bold color='#ffffffff' align=right>\n" ..
					 chooseText(language, "× button : Enter", "×ボタン : 決定") ..
		"		</textbox>" ..			 
			playstyle_menu(-0.01) ..
		"	</widget>" ..
		"</window>\n",

		SINGLE_USER_HIGH_SCORE_SCENE = single_play_high_score_scene_template,
		MULTI_USER_RECORD_SCENE	= multi_play_record_scene_template2,

		ONLINE_RANKING_SCENE =
		"<window>\n" ..
		"	<image id=bg/>" ..
		"	<widget id=safe_area>" ..
		"		<textbox id='' x=0.004 y=0.02 width=0.5 height=0.1 fontweight=bold color='#ffffffff' align=left>\n" ..
					 chooseText(language, "Online Ranking", "オンラインランキング") ..
		"		</textbox>" ..	
		"	</widget>" ..
		"</window>\n",

		PLAYER_JOIN_MENU_FOR_SINGLE_USER = 
		"<window>\n" ..
		"	<image id=bg/>" ..
		"	<widget id=safe_area>" ..
				user_profile_contents("userName", {0.03, 0.03}, {0.3, 0.08}, "bold",  "#ffffffff", "left", "userName")..
		"		<textbox id='playstyle' x=0.004 y=0.10 width=0.5 height=0.1 fontweight=bold color='#ffffffff' align=left>\n" ..
					 chooseText(language, "Play Style", "プレイスタイル") ..
		"		</textbox>" ..			 
		"		<textbox id='' x=0.000 y=0.92 width=1.0 height=0.08 fontweight=bold color='#ffffffff' align=right>\n" ..
					 chooseText(language, "× button : Enter　○ button : Back", "×ボタン : 決定　○ボタン : 戻る") ..
		"		</textbox>" ..			 
			playstyle_menu(0) ..
		"	</widget>" ..
		"</window>\n",

		PLAYER_JOIN_MENU0_FOR_MULTI_USER_PLAY_STYLE_MENU_SCENE = 
		"<window>\n" ..
		"	<image id=bg/>" ..
		"	<widget id=safe_area>" ..
				user_profile_contents("userName", {0.03, 0.03}, {0.3, 0.08}, "bold",  "#ffffffff", "left", "userName")..
				playstyle_menu(-0.16) ..
		"	</widget>" ..
		"</window>\n",

		PLAYER_JOIN_MENU1_FOR_MULTI_USER_PLAY_STYLE_MENU_SCENE = 
		"<window>\n" ..
		"	<image id=bg/>" ..
		"	<widget id=safe_area>" ..
				user_profile_contents("userName", {0.03, 0.03}, {0.3, 0.08}, "bold",  "#ffffffff", "left", "userName")..
				playstyle_menu(-0.16) ..
		"	</widget>" ..
		"</window>\n",

		PLAYER_JOIN_MENU2_FOR_MULTI_USER_PLAY_STYLE_MENU_SCENE = 
		"<window>\n" ..
		"	<image id=bg/>" ..
		"	<widget id=safe_area>" ..
				user_profile_contents("userName", {0.03, 0.89}, {0.3, 0.08}, "bold",  "#ffffffff", "left", "userName")..
				playstyle_menu(0.10) ..
		"	</widget>" ..
		"</window>\n",

		PLAYER_JOIN_MENU3_FOR_MULTI_USER_PLAY_STYLE_MENU_SCENE = 
		"<window>\n" ..
		"	<image id=bg/>" ..
		"	<widget id=safe_area>" ..
				user_profile_contents("userName", {0.03, 0.89}, {0.3, 0.08}, "bold",  "#ffffffff", "left", "userName")..
				playstyle_menu(0.10) ..
		"	</widget>" ..
		"</window>\n",

		GAME_SYSTEM_HUD_SINGLE =
		"<window>\n" ..
		"	<widget id=safe_area>" ..
			textBox("time",		 {0.08,	0.03}, {1.0, 0.05},	"bold",  "#ffffffff", "center", "TIME: 00")..
			textBox("center",	 {0.0,	0.32}, {1.0, 0.18},	"bold",	   "#ffffffff",	"center", "CENTER")..
			user_profile_contents("userName0", {0.03,	0.03}, {0.3, 0.05},	"bold",	 "#ffffffff", "left", "userName0")..
			textBox("score0",        {0.7,	0.03}, {0.3, 0.05},	"bold",	 "#ffffffff", "left", "score0")..

			bulletRemains(0, {0.03,	0.15}) ..
		"	<widget id=camera_image_area x=0.05 y=0.70 width=0.25 height=0.25 />" ..
			textBox("camera_error_message", {0.0,	0.60}, {1.0, 0.08},	"bold",	 "#ffff00ff", "center", "")..
			textBoxDetail("video_recording_notification", textpos({0.1, 0.95}, {0.1, 1.1}, {0.4, 0.05}, "left"), anim(0.8, "linear", "linear"), "bold", "#ff0000ff", "", {0,0}, 1) ..

		"	</widget>" ..
		"</window>\n",

		GAME_SYSTEM_HUD_MULTI =
		"<window>\n" ..
		"	<widget id=safe_area>" ..
			textBox("time",		 {0.0,	0.45}, {1.0, 0.10},	"bold",   "#ffffffff", "center", "")..
			textBox("center",	 {0.0,	0.32}, {1.0, 0.25},	"bold",	  "#ffffffff",	"center", "")..
			textBox("center_for_long_message",	 {0.0,	0.40}, {1.0, 0.10},	"bold",	  "#ffffffff",	"center", "")..			
			textBoxDetail("video_recording_notification", textpos({0.3, 0.88}, {0.3, 1.1}, {0.4, 0.05}, "center"), anim(0.8, "linear", "linear"), "bold", "#ff0000ff", "", {0,0}, 1) ..

			"	<widget x=0.0 y=0.0 width=0.5 height=0.5>" ..
			user_profile_contents("userName0", {0.02, 0.03}, {0.3, 0.07}, "bold",  "#ffffffff", "left", "userName0")..
			textBox("score0", {0.68, 0.03}, {0.3, 0.07}, "bold",	 "#ffffffff", "left", "")..
			bulletRemains(0, {0.03,	0.15}) ..
			textBox("cheerState0", {0.10,	0.14}, {0.3, 0.06},	"bold",	 "#ffffffff", "left", "")..
			textBox("cheeredCount0", {0.10,	0.21}, {0.3, 0.06},	"bold",	 "#ffffffff", "left", "")..
		"	<widget id=camera_image_area0 x=0.08 y=0.62 width=0.25 height=0.25 />" ..
			textBox("error_message0", {0.0,	0.55}, {1.0, 0.07},	"bold",	 "#ffff00ff", "center", "")..
			"	</widget>" ..

			"	<widget x=0.5 y=0.0 width=0.5 height=0.5>" ..
			user_profile_contents("userName1", {0.02, 0.03}, {0.3, 0.07}, "bold",  "#ffffffff", "left", "userName1")..
			textBox("score1", {0.68, 0.03}, {0.3, 0.07}, "bold",	 "#ffffffff", "left", "")..
			bulletRemains(1, {0.90,	0.15}) ..
			textBox("cheerState1", {0.10,	0.14}, {0.3, 0.06},	"bold",	 "#ffffffff", "left", "")..
			textBox("cheeredCount1", {0.10,	0.21}, {0.3, 0.06},	"bold",	 "#ffffffff", "left", "")..
		"	<widget id=camera_image_area1 x=0.63 y=0.62 width=0.25 height=0.25 />" ..
			textBox("error_message1", {0.0,	0.55}, {1.0, 0.07},	"bold",	 "#ffff00ff", "center", "")..
			"	</widget>" ..

			"	<widget x=0.0 y=0.5 width=0.5 height=0.5>" ..
			user_profile_contents("userName2", {0.02, 0.89}, {0.3, 0.07}, "bold",  "#ffffffff", "left", "userName2")..
			textBox("score2", {0.68, 0.89}, {0.3, 0.07}, "bold",	 "#ffffffff", "left", "")..
			bulletRemains(2, {0.03,	0.70}) ..
			textBox("cheerState2", {0.10,	0.74}, {0.3, 0.06},	"bold",	 "#ffffffff", "left", "")..
			textBox("cheeredCount2", {0.10,	0.81}, {0.3, 0.06},	"bold",	 "#ffffffff", "left", "")..
		"	<widget id=camera_image_area2 x=0.08 y=0.62 width=0.25 height=0.25 />" ..
			textBox("error_message2", {0.0,	0.55}, {1.0, 0.07},	"bold",	 "#ffff00ff", "center", "")..
			"	</widget>" ..

			"	<widget x=0.5 y=0.5 width=0.5 height=0.5>" ..
			user_profile_contents("userName3", {0.02, 0.89}, {0.3, 0.07}, "bold",  "#ffffffff", "left", "userName3")..
			textBox("score3", {0.68, 0.89}, {0.3, 0.07}, "bold",	 "#ffffffff", "left", "")..
			bulletRemains(3, {0.90,	0.70}) ..
			textBox("cheerState3", {0.10,	0.74}, {0.3, 0.06},	"bold",	 "#ffffffff", "left", "")..
			textBox("cheeredCount3", {0.10,	0.81}, {0.3, 0.06},	"bold",	 "#ffffffff", "left", "")..
		"	<widget id=camera_image_area3 x=0.63 y=0.62 width=0.25 height=0.25 />" ..
			textBox("error_message3", {0.0,	0.55}, {1.0, 0.07},	"bold",	 "#ffff00ff", "center", "")..
			"	</widget>" ..

		"	</widget>" ..
		"</window>\n",

		GAME_SYSTEM_HUD_ONLINE =
		"<window>\n" ..
		"	<widget id=safe_area>" ..
			textBox("time",		 {0.0,	0.07}, {1.0, 0.10},	"bold",   "#ffffffff", "center", "TIME: 00")..
			textBox("center",	 {0.0,	0.32}, {1.0, 0.25},	"bold",	  "#ffffffff",	"center", "CENTER")..
			textBox("center_for_long_message",	 {0.0,	0.40}, {1.0, 0.10},	"bold",	  "#ffffffff",	"center", "CENTER MESSAGE")..
			textBox("lower_for_long_message",	 {0.0,	0.70}, {1.0, 0.10},	"bold",	  "#ffffffff",	"center", "LOWER MESSAGE")..
			"	<widget id=camera_image_area x=0.20 y=0.64 width=0.25 height=0.25 />" ..
			textBox("camera_error_message", {0.0,	0.52}, {1.0, 0.08},	"bold",	 "#ffff00ff", "center", "")..
			textBoxDetail("video_recording_notification", textpos({0.3, 0.95}, {0.3, 1.1}, {0.4, 0.05}, "center"), anim(0.8, "linear", "linear"), "bold", "#ff0000ff", "", {0,0}, 1) ..

			"	<widget x=0.0 y=0.0 width=0.5 height=0.5>" ..
			user_profile_contents("userName0", {0.02, 0.03}, {0.3, 0.07}, "bold",  "#ffffffff", "left", "userName0")..
			textBox("score0", {0.68, 0.03}, {0.3, 0.07},	"bold",	 "#ffffffff", "left", "score0")..
			textBox("playstyle0", {0.03, 0.12}, {1.0, 0.07}, "bold",	 "#ffffffff", "center", "playstyle0")..
			bulletRemains(0, {0.03,	0.20}) ..
			textBox("cheerState0", {0.10,	0.20}, {0.3, 0.06},	"bold",	 "#ffffffff", "left", "")..
			textBox("cheeredCount0", {0.10,	0.27}, {0.3, 0.06},	"bold",	 "#ffffffff", "left", "")..
			"	</widget>" ..

			"	<widget x=0.5 y=0.0 width=0.5 height=0.5>" ..
			user_profile_contents("userName1", {0.02, 0.03}, {0.3, 0.07}, "bold",  "#ffffffff", "left", "userName1")..
			textBox("score1", {0.68, 0.03}, {0.3, 0.07},	"bold",	 "#ffffffff", "left", "score1")..
			textBox("playstyle1", {0.03, 0.12},	{1.0, 0.07}, "bold",	 "#ffffffff", "center",	"playstyle1")..
			bulletRemains(1, {0.90,	0.20}) ..
			textBox("cheerState1", {0.10,	0.20}, {0.3, 0.06},	"bold",	 "#ffffffff", "left", "")..
			textBox("cheeredCount1", {0.10,	0.27}, {0.3, 0.06},	"bold",	 "#ffffffff", "left", "")..
			"	</widget>" ..

			"	<widget x=0.0 y=0.5 width=0.5 height=0.5>" ..
			user_profile_contents("userName2", {0.02, 0.89}, {0.3, 0.07}, "bold",  "#ffffffff", "left", "userName2")..
			textBox("score2", {0.68, 0.89}, {0.3, 0.07},	"bold",	 "#ffffffff", "left", "score2")..
			textBox("playstyle2", {0.03, 0.79},	{1.0, 0.07}, "bold",	 "#ffffffff", "center",	"playstyle2")..
			bulletRemains(2, {0.03,	0.70}) ..
			textBox("cheerState2", {0.10,	0.64}, {0.3, 0.06},	"bold",	 "#ffffffff", "left", "")..
			textBox("cheeredCount2", {0.10,	0.71}, {0.3, 0.06},	"bold",	 "#ffffffff", "left", "")..
			"	</widget>" ..

			"	<widget x=0.5 y=0.5 width=0.5 height=0.5>" ..
			user_profile_contents("userName3", {0.02, 0.89}, {0.3, 0.07}, "bold",  "#ffffffff", "left", "userName3")..
			textBox("score3", {0.68, 0.89}, {0.3, 0.07},	"bold",	 "#ffffffff", "left", "score3")..
			textBox("playstyle3", {0.03, 0.79},	{1.0, 0.07}, "bold",	 "#ffffffff", "center",	"playstyle3")..
			bulletRemains(3, {0.90,	0.70}) ..
			textBox("cheerState3", {0.10,	0.64}, {0.3, 0.06},	"bold",	 "#ffffffff", "left", "")..
			textBox("cheeredCount3", {0.10,	0.71}, {0.3, 0.06},	"bold",	 "#ffffffff", "left", "")..
			"	</widget>" ..

		"	</widget>" ..
		"</window>\n",

		GAME_MULTI_RESULT =
		"<window>\n" ..
		"	<widget id=safe_area>" ..
		"	<widget x=0.1 y=0.1 width=0.8 height=0.8 bgcolor=#000000d0/>\n" ..
			textBox("rankingTitle", {0.0, 0.18}, {1.0, 0.1 },	"bold",	  "#ffff00ff",	"center", "RANKING")..

			textBox("rankNum0",	 {0.1,	0.3}, {0.05, 0.06},	"bold",	  "#ffffffff",	"center", "0")..
			user_profile_contents("rankName0", {0.15, 0.3}, {0.4, 0.06}, "bold",  "#ffffffff", "left", "name")..
			textBox("rankScore0",{0.65,	0.3}, {0.2, 0.06},	"normal", "#ffffffff",	"right",  "000000")..

			textBox("rankNum1",	 {0.1,	0.45}, {0.05, 0.06},	"bold",	  "#ffffffff",	"center", "0")..
			user_profile_contents("rankName1", {0.15, 0.45}, {0.4, 0.06}, "bold",  "#ffffffff", "left", "name")..
			textBox("rankScore1",{0.65, 0.45}, {0.2, 0.06},	"normal", "#ffffffff",	"right",  "000000")..

			textBox("rankNum2",	 {0.1,	0.6}, {0.05, 0.06},	"bold",	  "#ffffffff",	"center", "0")..
			user_profile_contents("rankName2", {0.15, 0.6}, {0.4, 0.06}, "bold",  "#ffffffff", "left", "name")..
			textBox("rankScore2",{0.65, 0.6}, {0.2, 0.06},	"normal", "#ffffffff",	"right",  "000000")..

			textBox("rankNum3",	 {0.1,	0.75}, {0.05, 0.06},	"bold",	  "#ffffffff",	"center", "0")..
			user_profile_contents("rankName3", {0.15, 0.75}, {0.4, 0.06}, "bold",  "#ffffffff", "left", "name")..
			textBox("rankScore3",{0.65, 0.75}, {0.2, 0.06},	"normal", "#ffffffff",	"right",  "000000")..
		"	</widget>" ..
		"</window>\n",

 		BG_ONLY_SCENE = 
		"<window>\n" ..
		"	<image id=bg/>" ..
		"</window>\n",
		
		ONLINE_MENU_SCENE =
		"<window>\n" ..
		"	<image id=bg/>" ..
		"	<widget id=safe_area>" ..
		"		<textbox id='' x=0.05 y=0.10 width=0.5 height=0.1 fontweight=bold color='#ffffffff' align=left>\n" ..
					 chooseText(language, "Online Menu", "オンラインメニュー") ..
		"		</textbox>" ..	
		"		<textbox id='create_room' x=0.3 y=0.25 width=0.4 height=0.08 fontweight=bold color='#ffffffff' align=center cursor_index_x=0 cursor_index_y=0>\n" ..
					 chooseText(language, "Create Room", "ルーム作成") ..
		"		</textbox>" ..	
		"		<textbox id='search_rooms' x=0.3 y=0.35 width=0.4 height=0.08 fontweight=bold color='#ffffffff' align=center cursor_index_x=0 cursor_index_y=1>\n" ..
					 chooseText(language, "Search Rooms", "ルーム検索") ..
		"		</textbox>" ..	
		"		<textbox id='message' x=0.5 y=0.8 width=0.5 height=0.04 fontweight=bold color='#ffff00ff' align=left>\n" ..
		"		</textbox>" ..	
		"		<textbox id='' x=0.000 y=0.95 width=1.0 height=0.05 hidey=1.00 animationtime=0.5 easein=cubicin fontweight=bold color='#ffffffff' align=right>\n" ..
					 chooseText(language, "○ button : Top Menu", "○ボタン : トップメニュー") ..
		"		</textbox>" ..
		"	</widget>" ..
		"</window>\n",

		ONLINE_ROOM_LIST_SCENE =
		"<window>\n" ..
		"	<image id=bg/>" ..
		"	<widget id=safe_area>" ..
		"		<textbox id='' x=0.05 y=0.10 width=0.5 height=0.1 fontweight=bold color='#ffffffff' align=left>\n" ..
					 chooseText(language, "Room List", "ルームリスト") ..
		"		</textbox>" ..	
		"		<textbox id='message' x=0.65 y=0.8 width=0.5 height=0.04 fontweight=bold color='#ffff00ff' align=left>\n" ..
		"		</textbox>" ..	
		"		<textbox id='' x=0.000 y=0.90 width=1.0 height=0.05 hidey=1.00 animationtime=0.5 easein=cubicin fontweight=bold color='#ffffffff' align=right>\n" ..
					 chooseText(language, "R1 button : Refresh", "R1ボタン : 更新") ..
		"		</textbox>" ..
		"		<textbox id='' x=0.000 y=0.95 width=1.0 height=0.05 hidey=1.00 animationtime=0.5 easein=cubicin fontweight=bold color='#ffffffff' align=right>\n" ..
					 chooseText(language, "○ button : Online Menu", "○ボタン : オンラインメニュー") ..
		"		</textbox>" ..
		"	</widget>" ..
		"</window>\n",

		ONLINE_ROOM_LIST_SCENE_CONTENT_FOR_NO_ROOM_CASE =
		"<window>\n" ..
		"	<widget id=safe_area>" ..
        "		<textbox id='' x=0.10 y=0.20 width=0.5 height=0.08 fontweight=bold color='#ff0000ff' align=left>\n" ..
	                 chooseText(language, "There is no room", "ルームがありません") ..
        "		</textbox>" ..	
		"	</widget>" ..		
		"</window>\n",

		ONLINE_ROOM_LIST_SCENE_CONTENT_TO_DISPLAY_LIST_HEADER =
		"<window>\n" ..
		"	<widget id=safe_area>" ..
		"		<textbox id='' x=0.08 y=0.20 width=0.4 height=0.08 fontweight=bold color='#ffff00ff' align=left>\n" ..
					 chooseText(language, "Room Name", "ルーム名") ..
		"		</textbox>" ..	
		"		<textbox id='' x=0.57 y=0.19 width=0.2 height=0.04 fontweight=bold color='#ffff00ff' align=center>\n" ..
					 chooseText(language, "Number of", "") ..
		"		</textbox>" ..	
		"		<textbox id='' x=0.57 y=0.24 width=0.2 height=0.04 fontweight=bold color='#ffff00ff' align=center>\n" ..
					 chooseText(language, "Members", "メンバー数") ..
		"		</textbox>" ..	
		"		<textbox id='' x=0.80 y=0.22 width=0.4 height=0.04 fontweight=bold color='#ffff00ff' align=left>\n" ..
					 chooseText(language, "Total Rooms:", "全ルーム数:") ..
		"		</textbox>" ..	
		"		<textbox id='num_rooms' x=0.95 y=0.22 width=0.4 height=0.04 fontweight=bold color='#ffff00ff' align=left>\n" ..
		"		</textbox>" ..	
		"	</widget>" ..
		"</window>\n",

		-- Scroll
		
		ONLINE_RANKING_SCENE_SCROLL = 
		"<scroll showingline=10 x=0.01 y=0.22 animationtime=0.25 width=0.98 height=0.63 barwidth=0.01 offset=0.02 barcolor='#2222bbff' barbgcolor='#aaaaffff' cursor=false>\n" ..
		"	<line>\n" ..
			textBox("score_item_rank", {0.0, 0.0}, {0.035, 0.0}, "bold", "#ffffffff", "left",  "")..
			textBox("score_item_value", {0.0, 0.0}, {0.062, 0.0}, "normal", "#ffffffff", "right",  "")..
			user_profile_contents("score_item_np_id", {0.0, 0.0}, {0.355, 0.0}, "bold",  "#ffffffff", "left", "")..
			textBox("score_item_comment", {0.0, 0.0}, {0.435, 0.0}, "bold", "#ffffffff", "left",  "")..
			textBox("score_item_account_id", {0.0, 0.0}, {0.0, 0.0}, "bold", "#ffffffff", "left",  "")..
		"	</line>\n" ..
		"</scroll>\n",

		ONLINE_ROOM_LIST_SCENE_SCROLL = 
		"<scroll showingrows=7 x=0.06 y=0.3 animationtime=0.25 width=0.70 height=0.6 barwidth=0.01 offset=0.02 barcolor='#2222bbff' barbgcolor='#aaaaffff' cursor=true>\n" ..
		"	<line>\n" ..		
			textBox("room_name", {0.0, 0.0}, {0.52, 0.0}, "bold", "#ffffffff", "left", "")..
			textBox("num_members", {0.0, 0.0}, {0.1, 0.0}, "bold", "#ffffffff", "center",  "")..
		"	</line>\n" ..
		"</scroll>\n",

		ONLINE_ROOM_SCENE =
		"<window>\n" ..
		"	<image id=bg/>" ..
		"	<widget id=safe_area>" ..
		"		<textbox id='' x=0.10 y=0.15 width=1.0 height=0.10 fontweight=bold color='#ffffffff' align=left>\n" ..
					 chooseText(language, "Room Member", "ルームメンバー") ..
		"		</textbox>" ..			 
		"		<textbox id='' x=0.02 y=0.32 width=0.2 height=0.05 fontweight=bold color='#ffff00ff' align=left>\n" ..
					 chooseText(language, "[Owner]", "[オーナー]") ..
		"		</textbox>" ..
				user_profile_contents("name0", {0.15, 0.32}, {0.3, 0.05}, "bold",  "#ffff00ff", "left", "")..			 
		"		<textbox id='state0'  x=0.65 y=0.32 width=0.3 height=0.05 fontweight=bold color='#ffff00ff' align=left>\n" ..
        "            "..		
		"		</textbox>" ..			 

				user_profile_contents("name1", {0.15, 0.38}, {0.3, 0.05}, "bold",  "#ffff00ff", "left", "")..			 
		"		<textbox id='state1'  x=0.65 y=0.38 width=0.3 height=0.05 fontweight=bold color='#ffff00ff' align=left>\n" ..
        "            "..		
		"		</textbox>" ..			 

				user_profile_contents("name2", {0.15, 0.44}, {0.3, 0.05}, "bold",  "#ffff00ff", "left", "")..			 
		"		<textbox id='state2'  x=0.65 y=0.44 width=0.3 height=0.05 fontweight=bold color='#ffff00ff' align=left>\n" ..
        "            "..		
		"		</textbox>" ..			 

				user_profile_contents("name3", {0.15, 0.50}, {0.3, 0.05}, "bold",  "#ffff00ff", "left", "")..			 
		"		<textbox id='state3'  x=0.65 y=0.50 width=0.3 height=0.05 fontweight=bold color='#ffff00ff' align=left>\n" ..
        "            "..		
		"		</textbox>" ..			 


		"		<textbox id='circle_button_behavior' x=0.05 y=0.80 width=0.45 height=0.05 fontweight=bold color='#ffffffff' align=left>\n" ..
					 chooseText(language, "○ button : Leave Room", "○ボタン : ルームから退出する") ..
		"		</textbox>" ..			 
		"		<textbox id='cross_button_behavior' x=0.50 y=0.80 width=0.45 height=0.05 fontweight=bold color='#ffffffff' align=right>\n" ..
					 chooseText(language, "× button : Start Game", "×ボタン : ゲームを開始する") ..
		"		</textbox>" ..			 
		"		<textbox id='' x=0.50 y=0.75 width=0.45 height=0.05 fontweight=bold color='#ffffffff' align=right>\n" ..
					 chooseText(language, "△ button : Send Invitation", "△ボタン : 招待を送る") ..
		"		</textbox>" ..			 
		"		<textbox id='connecting' x=0.15 y=0.32 width=0.3 height=0.05 fontweight=bold color='#00ffffff' align=left>\n" ..
		"		</textbox>" ..			 
		"		<textbox id='waiting_start' x=0.50 y=0.70 width=0.50 height=0.05 fontweight=bold color='#00ffffff' align=right>\n" ..
		"		</textbox>" ..			 
		"	</widget>" ..
		"</window>\n",				
		
		CAMERA_SETTING_SCENE = 
		"<window>\n" ..
		"	<widget id=safe_area>" ..
			textBox("error_message",  {0.05, 0.7}, {0.9, 0.08},	"bold",  "#ffff00ff",	"center", "")..
		"	<widget x=0.02 y=0.84 width=0.96 height=0.06 bgcolor=#000000d0>\n" ..
		"		<textbox id='' x=0.0 y=0.15 width=1.0 height=0.7 fontweight=bold color='#ffff00ff' align=center>\n" ..
					chooseText(language, "Fix PlayStationⓇCamera where light bar can appear in the image, and push × button",
											"画像内にライトバーが見える位置にPlayStationⓇCameraを固定し、×ボタンを押してください") ..
		"		</textbox>" ..	
		"	</widget>\n" ..
		"	<widget id=return_to_top_menu_widget x=0.68 y=0.94 width=0.30 height=0.06 hidex=1.5 hidey=1.5 animationtime=0.0 easein=immediate easeout=immediate bgcolor=#000000d0>\n" ..
		"		<textbox id='' x=0.0 y=0.15 width=1.0 height=0.7 fontweight=bold color='#ffff00ff' align=center>\n" ..
					chooseText(language, "○ button : Top Menu", "○ボタン : トップメニュー") ..
		"		</textbox>" ..	
		"	</widget>\n" ..
		"	</widget>" ..
		"</window>\n",

		PAD_TRACKER_OPERATION_RANGE_SETTING_SCENE = 
		"<window>\n" ..
		"	<widget id=safe_area>" ..
		"	<widget x=0.02 y=0.79 width=0.96 height=0.1 bgcolor=#000000d0>\n" ..
				textBox("message_top",	   {0.0, 0.1}, {1.0, 0.4},	"bold",	 "#ffff00ff",	"center", "")..
				textBox("message_bottom",  {0.0, 0.6}, {1.0, 0.4},	"bold",  "#ffff00ff",	"center", "")..
		"	</widget>\n" ..
		"	<widget id=return_to_top_menu_widget x=0.68 y=0.94 width=0.30 height=0.06 hidex=1.5 hidey=1.5 animationtime=0.0 easein=immediate easeout=immediate bgcolor=#000000d0>\n" ..
		"		<textbox id='' x=0.0 y=0.15 width=1.0 height=0.7 fontweight=bold color='#ffff00ff' align=center>\n" ..
					chooseText(language, "○ button : Top Menu", "○ボタン : トップメニュー") ..
		"		</textbox>" ..	
		"	</widget>\n" ..
		"	</widget>" ..
		"</window>\n",

		PAD_TRACKER_OPERATION_RANGE_SETTING_HUD = 
		"<window>\n" ..
		"	<widget id=safe_area>" ..
		"	<widget x=0.0 y=0.40 width=1.0 height=0.12 bgcolor=#000000d0>\n" ..
				textBox("error_message",   {0.0, 0.15}, {1.0, 0.7},	"bold",	 "#ffff00ff",	"center", "")..
		"	</widget>\n" ..
		"	</widget>" ..
		"</window>\n",
	}


