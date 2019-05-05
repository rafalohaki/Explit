#pragma once
#include "../../math/Vector.hpp"
#include "../../math/QAngle.hpp"
#include "../../math/VMatrix.hpp"

#define signonstate_none		0	// no state yet, about to connect
#define signonstate_challenge	1	// client challenging server, all oob packets
#define signonstate_connected	2	// client is connected to server, netchans ready
#define signonstate_new			3	// just got serverinfo and string tables
#define signonstate_prespawn	4	// received signon buffers
#define signonstate_spawn		5	// ready to receive entity packets
#define signonstate_full		6	// we are fully connected, first non-delta packet received
#define signonstate_changelevel	7	// server is changing level, please wait

#define flow_outgoing 0		
#define flow_incoming 1
#define max_flows 2	// in & out

typedef struct input_context_handle_t__ *input_context_handle_t;
struct client_text_message_t;
struct model_t;
class surf_info;
class i_material;
class c_sentence;
class c_audio_source;
class audio_state_t;
class is_patial_query;
class i_material_system;
class c_phys_collide;
class i_achievement_mgr;
class i_net_channel_info;
class is_pshared_memory;
class c_game_stats_data;
class key_values;
class c_steam_api_context;
struct frustum_t;

typedef void(*pfndemocustomdatacallback)(uint8_t *pdata, size_t isize);


typedef struct player_info_s
{
	__int64         unknown;            //0x0000 
	union
	{
		__int64       steamid64;          //0x0008 - steamid64
		struct
		{
			__int32     xuid_low;
			__int32     xuid_high;
		};
	};
	char            szname[128];        //0x0010 - player name
	int             userid;             //0x0090 - unique server identifier
	char            szsteamid[20];      //0x0094 - steam_x:y:z
	char            pad_0x00a8[0x10];   //0x00a8
	unsigned long   isteamid;           //0x00b8 - steamid 
	char            szfriendsname[128];
	bool            fakeplayer;
	bool            ishltv;
	unsigned int    customfiles[4];
	unsigned char   filesdownloaded;
} player_info_t;

class iv_engine_client
{
public:
	virtual int                   getintersectingsurfaces(const model_t *model, const Vector &vcenter, const float radius, const bool bonlyvisiblesurfaces, surf_info *pinfos, const int nmaxinfos) = 0;
	virtual Vector                getlightforpoint(const Vector &pos, bool bclamp) = 0;
	virtual i_material*            tracelinematerialandlighting(const Vector &start, const Vector &end, Vector &diffuselightcolor, Vector& basecolor) = 0;
	virtual const char*           parsefile(const char *data, char *token, int maxlen) = 0;
	virtual bool                  copyfile(const char *source, const char *destination) = 0;
	virtual void                  get_screen_size(int& width, int& height) = 0;
	virtual void                  servercmd(const char *szcmdstring, bool breliable = true) = 0;
	virtual void                  clientcmd(const char *szcmdstring) = 0;
	virtual bool                  getplayerinfo(int ent_num, player_info_t *pinfo) = 0;
	virtual int                   getplayerforuserid(int userid) = 0;
	virtual client_text_message_t* textmessageget(const char *pname) = 0; // 10
	virtual bool                  con_isvisible(void) = 0;
	virtual int                   get_local_player(void) = 0;
	virtual const model_t*        loadmodel(const char *pname, bool bprop = false) = 0;
	virtual float                 getlasttimestamp(void) = 0;
	virtual c_sentence*            getsentence(c_audio_source *paudiosource) = 0; // 15
	virtual float                 getsentencelength(c_audio_source *paudiosource) = 0;
	virtual bool                  isstreaming(c_audio_source *paudiosource) const = 0;
	virtual void                  get_view_angles(QAngle& va) = 0;
	virtual void                  set_view_angles(QAngle& va) = 0;
	virtual int                   get_max_clients(void) = 0; // 20
	virtual const char*           key_lookupbinding(const char *pbinding) = 0;
	virtual const char*           key_bindingforkey(int &code) = 0;
	virtual void                  key_setbinding(int, char const*) = 0;
	virtual void                  startkeytrapmode(void) = 0;
	virtual bool                  checkdonekeytrapping(int &code) = 0;
	virtual bool                  is_in_game(void) = 0;
	virtual bool                  is_connected(void) = 0;
	virtual bool                  isdrawingloadingimage(void) = 0;
	virtual void                  hideloadingplaque(void) = 0;
	virtual void                  con_nprintf(int pos, const char *fmt, ...) = 0; // 30
	virtual void                  con_nxprintf(const struct con_nprint_s *info, const char *fmt, ...) = 0;
	virtual int                   isboxvisible(const Vector& mins, const Vector& maxs) = 0;
	virtual int                   isboxinviewcluster(const Vector& mins, const Vector& maxs) = 0;
	virtual bool                  cullbox(const Vector& mins, const Vector& maxs) = 0;
	virtual void                  sound_extraupdate(void) = 0;
	virtual const char*           getgamedirectory(void) = 0;
	virtual const VMatrix&        world_to_screen_matrix() = 0;
	virtual const VMatrix&        worldtoviewmatrix() = 0;
	virtual int                   gamelumpversion(int lumpid) const = 0;
	virtual int                   gamelumpsize(int lumpid) const = 0; // 40
	virtual bool                  loadgamelump(int lumpid, void* pbuffer, int size) = 0;
	virtual int                   levelleafcount() const = 0;
	virtual is_patial_query*        getbsptreequery() = 0;
	virtual void                  lineartogamma(float* linear, float* gamma) = 0;
	virtual float                 lightstylevalue(int style) = 0; // 45
	virtual void                  computedynamiclighting(const Vector& pt, const Vector* pnormal, Vector& color) = 0;
	virtual void                  getambientlightcolor(Vector& color) = 0;
	virtual int                   getdxsupportlevel() = 0;
	virtual bool                  supportshdr() = 0;
	virtual void                  mat_stub(i_material_system *pmatsys) = 0; // 50
	virtual void                  getchaptername(char *pchbuff, int imaxlength) = 0;
	virtual char const*           getlevelname(void) = 0;
	virtual char const*           getlevelnameshort(void) = 0;
	virtual char const*           getmapgroupname(void) = 0;
	virtual struct ivoicetweak_s* getvoicetweakapi(void) = 0;
	virtual void                  setvoicecasterid(unsigned int someint) = 0; // 56
	virtual void                  enginestats_beginframe(void) = 0;
	virtual void                  enginestats_endframe(void) = 0;
	virtual void                  fireevents() = 0;
	virtual int                   getleavesarea(unsigned short *pleaves, int nleaves) = 0;
	virtual bool                  doesboxtouchareafrustum(const Vector &mins, const Vector &maxs, int iarea) = 0; // 60
	virtual int                   getfrustumlist(frustum_t **plist, int listmax) = 0;
	virtual bool                  shoulduseareafrustum(int i) = 0;
	virtual void                  setaudiostate(const audio_state_t& state) = 0;
	virtual int                   sentencegrouppick(int groupindex, char *name, int namebuflen) = 0;
	virtual int                   sentencegrouppicksequential(int groupindex, char *name, int namebuflen, int sentenceindex, int reset) = 0;
	virtual int                   sentenceindexfromname(const char *psentencename) = 0;
	virtual const char*           sentencenamefromindex(int sentenceindex) = 0;
	virtual int                   sentencegroupindexfromname(const char *pgroupname) = 0;
	virtual const char*           sentencegroupnamefromindex(int groupindex) = 0;
	virtual float                 sentencelength(int sentenceindex) = 0;
	virtual void                  computelighting(const Vector& pt, const Vector* pnormal, bool bclamp, Vector& color, Vector *pboxcolors = NULL) = 0;
	virtual void                  activateoccluder(int noccluderindex, bool bactive) = 0;
	virtual bool                  isoccluded(const Vector &vecabsmins, const Vector &vecabsmaxs) = 0; // 74
	virtual int                   getocclusionviewid(void) = 0;
	virtual void*                 saveallocmemory(size_t num, size_t size) = 0;
	virtual void                  savefreememory(void *psavemem) = 0;
	virtual i_net_channel_info*      get_net_channel_info(void) = 0;
	virtual void                  debugdrawphyscollide(const c_phys_collide *pcollide, i_material *pmaterial, const matrix3x4_t& transform, const uint8_t* color) = 0; //79
	virtual void                  checkpoint(const char *pname) = 0; // 80
	virtual void                  drawportals() = 0;
	virtual bool                  isplayingdemo(void) = 0;
	virtual bool                  isrecordingdemo(void) = 0;
	virtual bool                  isplayingtimedemo(void) = 0;
	virtual int                   getdemorecordingtick(void) = 0;
	virtual int                   getdemoplaybacktick(void) = 0;
	virtual int                   getdemoplaybackstarttick(void) = 0;
	virtual float                 getdemoplaybacktimescale(void) = 0;
	virtual int                   getdemoplaybacktotalticks(void) = 0;
	virtual bool                  ispaused(void) = 0; // 90
	virtual float                 gettimescale(void) const = 0;
	virtual bool                  istakingscreenshot(void) = 0;
	//virtual void				  unknown_0(void) = 0;
	virtual bool                  ishltv(void) = 0;
	virtual bool                  islevelmainmenubackground(void) = 0;
	virtual void                  getmainmenubackgroundname(char *dest, int destlen) = 0;
	virtual void                  setocclusionparameters(const int /*occlusionparams_t*/ &params) = 0; // 96
	virtual void                  getuilanguage(char *dest, int destlen) = 0;
	virtual int                   isskyboxvisiblefrompoint(const Vector &vecpoint) = 0;
	virtual const char*           getmapentitiesstring() = 0;
	virtual bool                  isineditmode(void) = 0; // 100
	virtual float                 getscreenaspectratio(int viewportwidth, int viewportheight) = 0;
	virtual bool                  removed_steamrefreshlogin(const char *password, bool issecure) = 0;
	virtual bool                  removed_steamprocesscall(bool & finished) = 0;
	virtual unsigned int          getenginebuildnumber() = 0; // engines build
	virtual const char *          getproductversionstring() = 0; // mods version number (steam.inf)
	virtual void                  grabprecolorcorrectedframe(int x, int y, int width, int height) = 0;
	virtual bool                  ishammerrunning() const = 0;
	virtual void                  executeclientcmd(const char *szcmdstring) = 0; //108
	virtual bool                  maphashdrlighting(void) = 0;
	virtual bool                  maphaslightmapalphadata(void) = 0;
	virtual int                   getappid() = 0;
	virtual Vector                getlightforpointfast(const Vector &pos, bool bclamp) = 0;
	virtual void                  clientcmd_unrestricted(char  const*, int, bool) = 0;
	virtual void                  clientcmd_unrestricted(const char *szcmdstring) = 0; // 114
	virtual void                  setrestrictservercommands(bool brestrict) = 0;
	virtual void                  setrestrictclientcommands(bool brestrict) = 0;
	virtual void                  setoverlaybindproxy(int ioverlayid, void *pbindproxy) = 0;
	virtual bool                  copyframebuffertomaterial(const char *pmaterialname) = 0;
	virtual void                  readconfiguration(const int icontroller, const bool readdefault) = 0;
	virtual void                  setachievementmgr(i_achievement_mgr *pachievementmgr) = 0;
	virtual i_achievement_mgr*      getachievementmgr() = 0;
	virtual bool                  maploadfailed(void) = 0;
	virtual void                  setmaploadfailed(bool bstate) = 0;
	virtual bool                  islowviolence() = 0;
	virtual const char*           getmostrecentsavegame(void) = 0;
	virtual void                  setmostrecentsavegame(const char *lpszfilename) = 0;
	virtual void                  startxboxexitingprocess() = 0;
	virtual bool                  issaveinprogress() = 0;
	virtual bool                  isautosavedangerousinprogress(void) = 0;
	virtual unsigned int          onstoragedeviceattached(int icontroller) = 0;
	virtual void                  onstoragedevicedetached(int icontroller) = 0;
	virtual char* const           getsavedirname(void) = 0;
	virtual void                  writescreenshot(const char *pfilename) = 0;
	virtual void                  resetdemointerpolation(void) = 0;
	virtual int                   getactivesplitscreenplayerslot() = 0;
	virtual int                   setactivesplitscreenplayerslot(int slot) = 0;
	virtual bool                  setlocalplayerisresolvable(char const *pchcontext, int nline, bool bresolvable) = 0;
	virtual bool                  islocalplayerresolvable() = 0;
	virtual int                   getsplitscreenplayer(int nslot) = 0;
	virtual bool                  issplitscreenactive() = 0;
	virtual bool                  isvalidsplitscreenslot(int nslot) = 0;
	virtual int                   firstvalidsplitscreenslot() = 0; // -1 == invalid
	virtual int                   nextvalidsplitscreenslot(int npreviousslot) = 0; // -1 == invalid
	virtual is_pshared_memory*      getsingleplayersharedmemoryspace(const char *szname, int ent_num = (1 << 11)) = 0;
	virtual void                  computelightingcube(const Vector& pt, bool bclamp, Vector *pboxcolors) = 0;
	virtual void                  registerdemocustomdatacallback(const char* szcallbacksaveid, pfndemocustomdatacallback pcallback) = 0;
	virtual void                  recorddemocustomdata(pfndemocustomdatacallback pcallback, const void *pdata, size_t idatalength) = 0;
	virtual void                  setpitchscale(float flpitchscale) = 0;
	virtual float                 getpitchscale(void) = 0;
	virtual bool                  loadfilmmaker() = 0;
	virtual void                  unloadfilmmaker() = 0;
	virtual void                  setleafflag(int nleafindex, int nflagbits) = 0;
	virtual void                  recalculatebspleafflags(void) = 0;
	virtual bool                  dspgetcurrentdasroomnew(void) = 0;
	virtual bool                  dspgetcurrentdasroomchanged(void) = 0;
	virtual bool                  dspgetcurrentdasroomskyabove(void) = 0;
	virtual float                 dspgetcurrentdasroomskypercent(void) = 0;
	virtual void                  setmixgroupofcurrentmixer(const char *szgroupname, const char *szparam, float val, int setmixertype) = 0;
	virtual int                   getmixlayerindex(const char *szmixlayername) = 0;
	virtual void                  setmixlayerlevel(int index, float level) = 0;
	virtual int                   getmixgroupindex(char  const* groupname) = 0;
	virtual void                  setmixlayertriggerfactor(int i1, int i2, float fl) = 0;
	virtual void                  setmixlayertriggerfactor(char  const* char1, char  const* char2, float fl) = 0;
	virtual bool                  iscreatingreslist() = 0;
	virtual bool                  iscreatingxboxreslist() = 0;
	virtual void                  settimescale(float fltimescale) = 0;
	virtual void                  setgamestatsdata(c_game_stats_data *pgamestatsdata) = 0;
	virtual c_game_stats_data*       getgamestatsdata() = 0;
	virtual void                  getmousedelta(int &dx, int &dy, bool b) = 0; // unknown
	virtual   const char*         key_lookupbindingex(const char *pbinding, int iuserid = -1, int istartcount = 0, int iallowjoystick = -1) = 0;
	virtual int                   key_codeforbinding(char  const*, int, int, int) = 0; // 186
	virtual void                  updatedandelights(void) = 0;
	virtual int                   getbugsubmissioncount() const = 0;
	virtual void                  clearbugsubmissioncount() = 0;
	virtual bool                  doeslevelcontainwater() const = 0;
	virtual float                 getserversimulationframetime() const = 0;
	virtual void                  solidmoved(class i_client_entity *psolident, class i_collideable *psolidcollide, const Vector* pprevabsorigin, bool accuratebboxtriggerchecks) = 0;
	virtual void                  triggermoved(class i_client_entity *ptriggerent, bool accuratebboxtriggerchecks) = 0;
	virtual void                  computeleavesconnected(const Vector &vecorigin, int ncount, const int *pleafindices, bool *pisconnected) = 0;
	virtual bool                  isincommentarymode(void) = 0;
	virtual void                  setblurfade(float amount) = 0;
	virtual bool                  istransitioningtoload() = 0;
	virtual void                  searchpathschangedafterinstall() = 0;
	virtual void                  configuresystemlevel(int ncpulevel, int ngpulevel) = 0;
	virtual void                  setconnectionpassword(char const *pchcurrentpw) = 0;
	virtual c_steam_api_context*     getsteamapicontext() = 0;
	virtual void                  submitstatrecord(char const *szmapname, unsigned int uiblobversion, unsigned int uiblobsize, const void *pvblob) = 0;
	virtual void                  servercmdkeyvalues(key_values *pkeyvalues) = 0; // 203
	virtual void                  spherepaintsurface(const model_t* model, const Vector& location, unsigned char chr, float fl1, float fl2) = 0;
	virtual bool                  haspaintmap(void) = 0;
	virtual void                  enablepaintmaprender() = 0;
	//virtual void                tracepaintsurface( const model_t *model, const Vector& position, float radius, cutlVector<color>& surfcolors ) = 0;
	virtual void                  spheretracepaintsurface(const model_t* model, const Vector& position, const Vector &vec2, float radius, /*cutlVector<unsigned char, cutlmemory<unsigned char, int>>*/ int& utilvecshit) = 0;
	virtual void                  removeallpaint() = 0;
	virtual void                  paintallsurfaces(unsigned char uchr) = 0;
	virtual void                  removepaint(const model_t* model) = 0;
	virtual bool                  isactiveapp() = 0;
	virtual bool                  isclientlocaltoactiveserver() = 0;
	virtual void                  tickprogressbar() = 0;
	virtual input_context_handle_t  getinputcontext(int /*engineinputcontextid_t*/ id) = 0;
	virtual void                  getstartupimage(char* filename, int size) = 0;
	virtual bool                  isusinglocalnetworkbackdoor(void) = 0;
	virtual void                  savegame(const char*, bool, char*, int, char*, int) = 0;
	virtual void                  getgenericmemorystats(/* genericmemorystat_t */ void **) = 0;
	virtual bool                  gamehasshutdownandflushedmemory(void) = 0;
	virtual int                   getlastacknowledgedcommand(void) = 0;
	virtual void                  finishcontainerwrites(int i) = 0;
	virtual void                  finishasyncsave(void) = 0;
	virtual int                   getservertick(void) = 0;
	virtual const char*           getmoddirectory(void) = 0;
	virtual bool                  audiolanguagechanged(void) = 0;
	virtual bool                  isautosaveinprogress(void) = 0;
	virtual void                  startloadingscreenforcommand(const char* command) = 0;
	virtual void                  startloadingscreenforkeyvalues(key_values* values) = 0;
	virtual void                  sossetopvarfloat(const char*, float) = 0;
	virtual void                  sosgetopvarfloat(const char*, float &) = 0;
	virtual bool                  issubscribedmap(const char*, bool) = 0;
	virtual bool                  isfeaturedmap(const char*, bool) = 0;
	virtual void                  getdemoplaybackparameters(void) = 0;
	virtual int                   getclientversion(void) = 0;
	virtual bool                  isdemoskipping(void) = 0;
	virtual void                  setdemoimportanteventdata(const key_values* values) = 0;
	virtual void                  clearevents(void) = 0;
	virtual int                   getsafezonexmin(void) = 0;
	virtual bool                  isvoicerecording(void) = 0;
	virtual void                  forcevoicerecordon(void) = 0;
	virtual bool                  isreplay(void) = 0;
};

class i_net_channel_info
{
public:

	enum
	{
		generic = 0,	// must be first and is default group
		localplayer,	// bytes for local player entity update
		otherplayers,	// bytes for other players update
		entities,		// all other entity bytes
		sounds,			// game sounds
		events,			// event messages
		tempents,		// temp entities
		usermessages,	// user messages
		entmessages,	// entity messages
		voice,			// voice data
		stringtable,	// a stringtable update
		move,			// client move cmds
		stringcmd,		// string command
		signon,			// various signondata
		total,			// must be last and is not a real group
	};

	virtual const char  *getname(void) const = 0;	// get channel name
	virtual const char  *getaddress(void) const = 0; // get channel ip address as string
	virtual float		gettime(void) const = 0;	// current net time
	virtual float		gettimeconnected(void) const = 0;	// get connection time in seconds
	virtual int			getbuffersize(void) const = 0;	// netchannel packet history size
	virtual int			getdatarate(void) const = 0; // send data rate in byte/sec

	virtual bool		isloopback(void) const = 0;	// true if loopback channel
	virtual bool		istimingout(void) const = 0;	// true if timing out
	virtual bool		isplayback(void) const = 0;	// true if demo playback

	virtual float		get_latency(int flow) const = 0;	 // current latency (rtt), more accurate but jittering
	virtual float		get_avg_latency(int flow) const = 0; // average packet latency in seconds
	virtual float		get_avg_loss(int flow) const = 0;	 // avg packet loss[0..1]
	virtual float		get_avg_choke(int flow) const = 0;	 // avg packet choke[0..1]
	virtual float		get_avg_data(int flow) const = 0;	 // data flow in bytes/sec
	virtual float		get_avg_packets(int flow) const = 0; // avg packets/sec
	virtual int			gettotaldata(int flow) const = 0;	 // total flow in/out in bytes
	virtual int			gettotalpackets(int flow) const = 0;
	virtual int			getsequencenr(int flow) const = 0;	// last send seq number
	virtual bool		isvalidpacket(int flow, int frame_number) const = 0; // true if packet was not lost/dropped/chocked/flushed
	virtual float		getpackettime(int flow, int frame_number) const = 0; // time when packet was send
	virtual int			getpacketbytes(int flow, int frame_number, int group) const = 0; // group size of this packet
	virtual bool		getstreamprogress(int flow, int *received, int *total) const = 0;  // tcp progress if transmitting
	virtual float		gettimesincelastreceived(void) const = 0;	// get time since last recieved packet in seconds
	virtual	float		getcommandinterpolationamount(int flow, int frame_number) const = 0;
	virtual void		getpacketresponselatency(int flow, int frame_number, int *pnlatencymsecs, int *pnchoke) const = 0;
	virtual void		getremoteframerate(float *pflframetime, float *pflframetimestddeviation) const = 0;

	virtual float		gettimeoutseconds() const = 0;
};