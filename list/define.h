/**************************************************
	A2dp status
**************************************************/
typedef struct {
	uint8 active;
	uint8 streaming;
	uint8 channels;
	uint8 bits;
	uint32 freq;
}BT_AVP_A2DP_STATUS_T;

/**************************************************
	Playback status
**************************************************/
typedef struct {
	uint8 playstatus;
	uint32 Song_length;
	uint32 Play_position;
}BT_AVP_PLAYBACK_STATUS_T;

/**************************************************
	Playback status
**************************************************/
typedef struct {
	uint16 charset;
	uint16 len;
	uint8 attribute;
}BT_AVP_METADATA_INFO_T;

/**************************************************
	Avrcp  status
**************************************************/
typedef struct {
	uint16 version;
	uint32 featureMask;
	uint32 Support_notification;
	uint32 Registed_notification;
	BT_AVP_PLAYBACK_STATUS_T Play_status;
	BT_AVP_METADATA_INFO_T Meta_data[8];
}BT_AVP_AVRCP_STATUS_T;

/**************************************************
	Status info for avrcp browsing
**************************************************/
typedef struct {
	uint16 Number_player;
}BT_AVP_BROWSING_STATUS_T;

/**************************************************
	Avp (a2dp & avrcp status).
**************************************************/
typedef struct {
	BT_STATUS_STRUCT_HEAD;
	uint8 connId;
	BT_AVP_A2DP_STATUS_T A2dp;
	BT_AVP_AVRCP_STATUS_T avrcp;
	BT_AVP_BROWSING_STATUS_T browsing;
}BT_AVP_STATUS_T;

#define SET_AVP_CONNID_ITEM(value) 	SET_ITEM(connId, value)

#define GET_AVP_CONNID_ITEM(valuePtr) 	 GET_ITEM_VALUE(connId, valuePtr)

#define SET_BT_AVP_CONNID_STATUS(addr, value) SET_BT_STATUS(BT_AVP_STATUS, addr, connId, value)

#define GET_BT_AVP_CONNID_STATUS(addr, value) GET_BT_VALUE_STATUS(BT_AVP_STATUS, addr, connId, value)

#define SET_AVP_A2DP_ACTIVE_ITEM(value) 	SET_ITEM(A2dp.active, value)

#define GET_AVP_A2DP_ACTIVE_ITEM(valuePtr) 	 GET_ITEM_VALUE(A2dp.active, valuePtr)

#define SET_BT_AVP_A2DP_ACTIVE_STATUS(addr, value) SET_BT_STATUS(BT_AVP_STATUS, addr, A2dp.active, value)

#define GET_BT_AVP_A2DP_ACTIVE_STATUS(addr, value) GET_BT_VALUE_STATUS(BT_AVP_STATUS, addr, A2dp.active, value)

#define SET_AVP_A2DP_STREAMING_ITEM(value) 	SET_ITEM(A2dp.streaming, value)

#define GET_AVP_A2DP_STREAMING_ITEM(valuePtr) 	 GET_ITEM_VALUE(A2dp.streaming, valuePtr)

#define SET_BT_AVP_A2DP_STREAMING_STATUS(addr, value) SET_BT_STATUS(BT_AVP_STATUS, addr, A2dp.streaming, value)

#define GET_BT_AVP_A2DP_STREAMING_STATUS(addr, value) GET_BT_VALUE_STATUS(BT_AVP_STATUS, addr, A2dp.streaming, value)

#define SET_AVP_A2DP_CHANNELS_ITEM(value) 	SET_ITEM(A2dp.channels, value)

#define GET_AVP_A2DP_CHANNELS_ITEM(valuePtr) 	 GET_ITEM_VALUE(A2dp.channels, valuePtr)

#define SET_BT_AVP_A2DP_CHANNELS_STATUS(addr, value) SET_BT_STATUS(BT_AVP_STATUS, addr, A2dp.channels, value)

#define GET_BT_AVP_A2DP_CHANNELS_STATUS(addr, value) GET_BT_VALUE_STATUS(BT_AVP_STATUS, addr, A2dp.channels, value)

#define SET_AVP_A2DP_BITS_ITEM(value) 	SET_ITEM(A2dp.bits, value)

#define GET_AVP_A2DP_BITS_ITEM(valuePtr) 	 GET_ITEM_VALUE(A2dp.bits, valuePtr)

#define SET_BT_AVP_A2DP_BITS_STATUS(addr, value) SET_BT_STATUS(BT_AVP_STATUS, addr, A2dp.bits, value)

#define GET_BT_AVP_A2DP_BITS_STATUS(addr, value) GET_BT_VALUE_STATUS(BT_AVP_STATUS, addr, A2dp.bits, value)

#define SET_AVP_A2DP_FREQ_ITEM(value) 	SET_ITEM(A2dp.freq, value)

#define GET_AVP_A2DP_FREQ_ITEM(valuePtr) 	 GET_ITEM_VALUE(A2dp.freq, valuePtr)

#define SET_BT_AVP_A2DP_FREQ_STATUS(addr, value) SET_BT_STATUS(BT_AVP_STATUS, addr, A2dp.freq, value)

#define GET_BT_AVP_A2DP_FREQ_STATUS(addr, value) GET_BT_VALUE_STATUS(BT_AVP_STATUS, addr, A2dp.freq, value)

#define SET_AVP_A2DP_ITEM(buffer) \
		 COPY_ITEM(A2dp, buffer, sizeof(A2dp))

#define GET_AVP_A2DP_ITEM(buffer) 	 GET_ITEM_COPY(A2dp, buffer, sizeof(A2dp))

#define SET_BT_AVP_A2DP_STATUS(addr, buffer) COPY_BT_STATUS(BT_AVP_STATUS, addr, A2dp, value, sizeof(A2dp))

#define GET_BT_AVP_A2DP_STATUS(addr, buffer) GET_BT_COPY_STATUS(BT_AVP_STATUS, addr, A2dp, value, sizeof(A2dp))

#define SET_AVP_AVRCP_VERSION_ITEM(value) 	SET_ITEM(avrcp.version, value)

#define GET_AVP_AVRCP_VERSION_ITEM(valuePtr) 	 GET_ITEM_VALUE(avrcp.version, valuePtr)

#define SET_BT_AVP_AVRCP_VERSION_STATUS(addr, value) SET_BT_STATUS(BT_AVP_STATUS, addr, avrcp.version, value)

#define GET_BT_AVP_AVRCP_VERSION_STATUS(addr, value) GET_BT_VALUE_STATUS(BT_AVP_STATUS, addr, avrcp.version, value)

#define SET_AVP_AVRCP_FEATUREMASK_ITEM(value) 	SET_ITEM(avrcp.featureMask, value)

#define GET_AVP_AVRCP_FEATUREMASK_ITEM(valuePtr) 	 GET_ITEM_VALUE(avrcp.featureMask, valuePtr)

#define SET_BT_AVP_AVRCP_FEATUREMASK_STATUS(addr, value) SET_BT_STATUS(BT_AVP_STATUS, addr, avrcp.featureMask, value)

#define GET_BT_AVP_AVRCP_FEATUREMASK_STATUS(addr, value) GET_BT_VALUE_STATUS(BT_AVP_STATUS, addr, avrcp.featureMask, value)

#define SET_AVP_AVRCP_SUPPORT_NOTIFICATION_ITEM(value) 	SET_ITEM(avrcp.Support_notification, value)

#define GET_AVP_AVRCP_SUPPORT_NOTIFICATION_ITEM(valuePtr) 	 GET_ITEM_VALUE(avrcp.Support_notification, valuePtr)

#define SET_BT_AVP_AVRCP_SUPPORT_NOTIFICATION_STATUS(addr, value) SET_BT_STATUS(BT_AVP_STATUS, addr, avrcp.Support_notification, value)

#define GET_BT_AVP_AVRCP_SUPPORT_NOTIFICATION_STATUS(addr, value) GET_BT_VALUE_STATUS(BT_AVP_STATUS, addr, avrcp.Support_notification, value)

#define SET_AVP_AVRCP_REGISTED_NOTIFICATION_ITEM(value) 	SET_ITEM(avrcp.Registed_notification, value)

#define GET_AVP_AVRCP_REGISTED_NOTIFICATION_ITEM(valuePtr) 	 GET_ITEM_VALUE(avrcp.Registed_notification, valuePtr)

#define SET_BT_AVP_AVRCP_REGISTED_NOTIFICATION_STATUS(addr, value) SET_BT_STATUS(BT_AVP_STATUS, addr, avrcp.Registed_notification, value)

#define GET_BT_AVP_AVRCP_REGISTED_NOTIFICATION_STATUS(addr, value) GET_BT_VALUE_STATUS(BT_AVP_STATUS, addr, avrcp.Registed_notification, value)

#define SET_AVP_AVRCP_PLAY_STATUS_PLAYSTATUS_ITEM(value) 	SET_ITEM(avrcp.Play_status.playstatus, value)

#define GET_AVP_AVRCP_PLAY_STATUS_PLAYSTATUS_ITEM(valuePtr) 	 GET_ITEM_VALUE(avrcp.Play_status.playstatus, valuePtr)

#define SET_BT_AVP_AVRCP_PLAY_STATUS_PLAYSTATUS_STATUS(addr, value) SET_BT_STATUS(BT_AVP_STATUS, addr, avrcp.Play_status.playstatus, value)

#define GET_BT_AVP_AVRCP_PLAY_STATUS_PLAYSTATUS_STATUS(addr, value) GET_BT_VALUE_STATUS(BT_AVP_STATUS, addr, avrcp.Play_status.playstatus, value)

#define SET_AVP_AVRCP_PLAY_STATUS_SONG_LENGTH_ITEM(value) 	SET_ITEM(avrcp.Play_status.Song_length, value)

#define GET_AVP_AVRCP_PLAY_STATUS_SONG_LENGTH_ITEM(valuePtr) 	 GET_ITEM_VALUE(avrcp.Play_status.Song_length, valuePtr)

#define SET_BT_AVP_AVRCP_PLAY_STATUS_SONG_LENGTH_STATUS(addr, value) SET_BT_STATUS(BT_AVP_STATUS, addr, avrcp.Play_status.Song_length, value)

#define GET_BT_AVP_AVRCP_PLAY_STATUS_SONG_LENGTH_STATUS(addr, value) GET_BT_VALUE_STATUS(BT_AVP_STATUS, addr, avrcp.Play_status.Song_length, value)

#define SET_AVP_AVRCP_PLAY_STATUS_PLAY_POSITION_ITEM(value) 	SET_ITEM(avrcp.Play_status.Play_position, value)

#define GET_AVP_AVRCP_PLAY_STATUS_PLAY_POSITION_ITEM(valuePtr) 	 GET_ITEM_VALUE(avrcp.Play_status.Play_position, valuePtr)

#define SET_BT_AVP_AVRCP_PLAY_STATUS_PLAY_POSITION_STATUS(addr, value) SET_BT_STATUS(BT_AVP_STATUS, addr, avrcp.Play_status.Play_position, value)

#define GET_BT_AVP_AVRCP_PLAY_STATUS_PLAY_POSITION_STATUS(addr, value) GET_BT_VALUE_STATUS(BT_AVP_STATUS, addr, avrcp.Play_status.Play_position, value)

#define SET_AVP_AVRCP_PLAY_STATUS_ITEM(buffer) \
		 COPY_ITEM(avrcp.Play_status, buffer, sizeof(avrcp.Play_status))

#define GET_AVP_AVRCP_PLAY_STATUS_ITEM(buffer) 	 GET_ITEM_COPY(avrcp.Play_status, buffer, sizeof(avrcp.Play_status))

#define SET_BT_AVP_AVRCP_PLAY_STATUS_STATUS(addr, buffer) COPY_BT_STATUS(BT_AVP_STATUS, addr, avrcp.Play_status, value, sizeof(avrcp.Play_status))

#define GET_BT_AVP_AVRCP_PLAY_STATUS_STATUS(addr, buffer) GET_BT_COPY_STATUS(BT_AVP_STATUS, addr, avrcp.Play_status, value, sizeof(avrcp.Play_status))

#define SET_AVP_AVRCP_META_DATA_ITEM(buffer) \
		 COPY_ITEM(avrcp.Meta_data, buffer, sizeof(avrcp.Meta_data))

#define SET_AVP_AVRCP_META_DATA_INDEX_ITEM(index, value) 	 SET_ITEM(avrcp.Meta_data[index], value)

#define GET_AVP_AVRCP_META_DATA_ITEM(buffer) GET_ITEM_COPY(buffer, &(avrcp.Meta_data), sizeof(avrcp.Meta_data))

#define GET_AVP_AVRCP_META_DATA_INDEX_ITEM(index, valuePtr) 	GET_ITEM_VALUE(avrcp.Meta_data[index], valuePtr)

#define SET_BT_AVP_AVRCP_META_DATA_INDEX_STATUS(addr, value) SET_BT_STATUS(BT_AVP_STATUS, addr, avrcp.Meta_data[index], value)

#define SET_BT_AVP_AVRCP_META_DATA_STATUS(addr, value) COPY_BT_STATUS(BT_AVP_STATUS, addr, avrcp.Meta_data, value, sizeof(avrcp.Meta_data))

#define GET_BT_AVP_AVRCP_META_DATA_STATUS(addr, value) GET_BT_COPY_STATUS(BT_AVP_STATUS, addr, avrcp.Meta_data, value, sizeof(avrcp.Meta_data))

#define GET_BT_AVP_AVRCP_META_DATA_INDEX_STATUS(addr, value) GET_BT_VALUE_STATUS(BT_AVP_STATUS, addr, avrcp.Meta_data[index], value)

#define SET_AVP_AVRCP_ITEM(buffer) \
		 COPY_ITEM(avrcp, buffer, sizeof(avrcp))

#define GET_AVP_AVRCP_ITEM(buffer) 	 GET_ITEM_COPY(avrcp, buffer, sizeof(avrcp))

#define SET_BT_AVP_AVRCP_STATUS(addr, buffer) COPY_BT_STATUS(BT_AVP_STATUS, addr, avrcp, value, sizeof(avrcp))

#define GET_BT_AVP_AVRCP_STATUS(addr, buffer) GET_BT_COPY_STATUS(BT_AVP_STATUS, addr, avrcp, value, sizeof(avrcp))

#define SET_AVP_BROWSING_NUMBER_PLAYER_ITEM(value) 	SET_ITEM(browsing.Number_player, value)

#define GET_AVP_BROWSING_NUMBER_PLAYER_ITEM(valuePtr) 	 GET_ITEM_VALUE(browsing.Number_player, valuePtr)

#define SET_BT_AVP_BROWSING_NUMBER_PLAYER_STATUS(addr, value) SET_BT_STATUS(BT_AVP_STATUS, addr, browsing.Number_player, value)

#define GET_BT_AVP_BROWSING_NUMBER_PLAYER_STATUS(addr, value) GET_BT_VALUE_STATUS(BT_AVP_STATUS, addr, browsing.Number_player, value)

#define SET_AVP_BROWSING_ITEM(buffer) \
		 COPY_ITEM(browsing, buffer, sizeof(browsing))

#define GET_AVP_BROWSING_ITEM(buffer) 	 GET_ITEM_COPY(browsing, buffer, sizeof(browsing))

#define SET_BT_AVP_BROWSING_STATUS(addr, buffer) COPY_BT_STATUS(BT_AVP_STATUS, addr, browsing, value, sizeof(browsing))

#define GET_BT_AVP_BROWSING_STATUS(addr, buffer) GET_BT_COPY_STATUS(BT_AVP_STATUS, addr, browsing, value, sizeof(browsing))

