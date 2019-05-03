#pragma once

typedef enum
{
	dpt_int = 0,
	dpt_float,
	dpt_vector,
	dpt_vectorxy,
	dpt_string,
	dpt_array,
	dpt_datatable,
	dpt_int64,
	dpt_numsendproptypes
} sendproptype;

class recvprop;
class recvtable;
class dvariant;

// this is passed into recvproxy functions.
class crecvproxydata;

//-----------------------------------------------------------------------------
// pstruct = the base structure of the datatable this variable is in (like c_base_entity)
// pout    = the variable that this this proxy represents (like c_base_entity::somevalue).
//
// convert the network-standard-type value in value into your own format in pstruct/pout.
//-----------------------------------------------------------------------------
typedef void(*recvvarproxyfn)(const crecvproxydata *pdata, void *pstruct, void *pout);

// ------------------------------------------------------------------------ //
// arraylengthrecvproxies are optionally used to get the length of the 
// incoming array when it changes.
// ------------------------------------------------------------------------ //
typedef void(*arraylengthrecvproxyfn)(void *pstruct, int objectid, int currentarraylength);


// note: datatable receive proxies work differently than the other proxies.
// pdata points at the object + the recv table's offset.
// pout should be set to the location of the object to unpack the data table into.
// if the parent object just contains the child object, the default proxy just does *pout = pdata.
// if the parent object points at the child object, you need to dereference the pointer here.
// note: don't ever return null from a datatable receive proxy function. bad things will happen.
typedef void(*datatablerecvvarproxyfn)(const recvprop *pprop, void **pout, void *pdata, int objectid);

class recvprop
{
	// this info comes from the receive data table.
public:
	recvprop();

	void                        initarray(int nelements, int elementstride);

	int                         getnumelements() const;
	void                        setnumelements(int nelements);

	int                         getelementstride() const;
	void                        setelementstride(int stride);

	int                         getflags() const;

	const char*                 getname() const;
	sendproptype                gettype() const;

	recvtable*                  getdatatable() const;
	void                        setdatatable(recvtable *ptable);

	recvvarproxyfn              getproxyfn() const;
	void                        setproxyfn(recvvarproxyfn fn);

	datatablerecvvarproxyfn     getdatatableproxyfn() const;
	void                        setdatatableproxyfn(datatablerecvvarproxyfn fn);

	int                         getoffset() const;
	void                        setoffset(int o);

	// arrays only.
	recvprop*                   getarrayprop() const;
	void                        setarrayprop(recvprop *pprop);

	// arrays only.
	void                        setarraylengthproxy(arraylengthrecvproxyfn proxy);
	arraylengthrecvproxyfn      getarraylengthproxy() const;

	bool                        isinsidearray() const;
	void                        setinsidearray();

	// some property types bind more data to the prop in here.
	const void*                 getextradata() const;
	void                        setextradata(const void *pdata);

	// if it's one of the numbered "000", "001", etc properties in an array, then
	// these can be used to get its array property name for debugging.
	const char*                 getparentarraypropname();
	void                        setparentarraypropname(const char *parraypropname);

public:

	const char                  *pvarname;
	sendproptype                recvtype;
	int                         flags;
	int                         stringbuffersize;


public:

	bool                        binsidearray;        // set to true by the engine if this property sits inside an array.

												   // extra data that certain special property types bind to the property here.
	const void *pextradata;

	// if this is an array (dpt_array).
	recvprop                    *parrayprop;
	arraylengthrecvproxyfn      arraylengthproxy;

	recvvarproxyfn              proxyfn;
	datatablerecvvarproxyfn     datatableproxyfn;    // for rdt_datatable.

	recvtable                   *pdatatable;        // for rdt_datatable.
	int                         offset;

	int                         elementstride;
	int                         nelements;

	// if it's one of the numbered "000", "001", etc properties in an array, then
	// these can be used to get its array property name for debugging.
	const char                  *pparentarraypropname;
};

class crecvdecoder;
class recvtable
{
public:

	typedef recvprop    proptype;

	recvtable();
	recvtable(recvprop *pprops, int nprops, const char *pnettablename);
	~recvtable();

	void                construct(recvprop *pprops, int nprops, const char *pnettablename);

	int                 getnumprops();
	recvprop*           getprop(int i);

	const char*         getname();

	// used by the engine while initializing array props.
	void                setinitialized(bool binitialized);
	bool                isinitialized() const;

	// used by the engine.
	void                setinmainlist(bool binlist);
	bool                isinmainlist() const;


public:

	// properties described in a table.
	recvprop           *pprops;
	int                 nprops;

	// the decoder. note: this covers each recvtable and all its children (ie: its children
	// will have their own decoders that include props for all their children).
	crecvdecoder       *pdecoder;

	const char         *pnettablename;    // the name matched between client and server.


private:

	bool                binitialized;
	bool                binmainlist;
};



inline int recvtable::getnumprops()
{
	return this->nprops;
}

inline recvprop* recvtable::getprop(int i)
{
	return &this->pprops[i];
}

inline const char* recvtable::getname()
{
	return this->pnettablename;
}

inline void recvtable::setinitialized(bool binitialized)
{
	this->binitialized = binitialized;
}

inline bool recvtable::isinitialized() const
{
	return this->binitialized;
}

inline void recvtable::setinmainlist(bool binlist)
{
	this->binmainlist = binlist;
}

inline bool recvtable::isinmainlist() const
{
	return this->binmainlist;
}


inline void recvprop::initarray(int nelements, int elementstride)
{
	this->recvtype = dpt_array;
	this->nelements = nelements;
	this->elementstride = elementstride;
}

inline int recvprop::getnumelements() const
{
	return this->nelements;
}

inline void recvprop::setnumelements(int nelements)
{
	this->nelements = nelements;
}

inline int recvprop::getelementstride() const
{
	return this->elementstride;
}

inline void recvprop::setelementstride(int stride)
{
	this->elementstride = stride;
}

inline int recvprop::getflags() const
{
	return this->flags;
}

inline const char* recvprop::getname() const
{
	return this->pvarname;
}

inline sendproptype recvprop::gettype() const
{
	return this->recvtype;
}

inline recvtable* recvprop::getdatatable() const
{
	return this->pdatatable;
}

inline void recvprop::setdatatable(recvtable *ptable)
{
	this->pdatatable = ptable;
}

inline recvvarproxyfn recvprop::getproxyfn() const
{
	return this->proxyfn;
}

inline void recvprop::setproxyfn(recvvarproxyfn fn)
{
	this->proxyfn = fn;
}

inline datatablerecvvarproxyfn recvprop::getdatatableproxyfn() const
{
	return this->datatableproxyfn;
}

inline void recvprop::setdatatableproxyfn(datatablerecvvarproxyfn fn)
{
	this->datatableproxyfn = fn;
}

inline int recvprop::getoffset() const
{
	return this->offset;
}

inline void recvprop::setoffset(int o)
{
	this->offset = o;
}

inline recvprop* recvprop::getarrayprop() const
{
	return this->parrayprop;
}

inline void recvprop::setarrayprop(recvprop *pprop)
{
	this->parrayprop = pprop;
}

inline void recvprop::setarraylengthproxy(arraylengthrecvproxyfn proxy)
{
	this->arraylengthproxy = proxy;
}

inline arraylengthrecvproxyfn recvprop::getarraylengthproxy() const
{
	return this->arraylengthproxy;
}

inline bool recvprop::isinsidearray() const
{
	return this->binsidearray;
}

inline void recvprop::setinsidearray()
{
	this->binsidearray = true;
}

inline const void* recvprop::getextradata() const
{
	return this->pextradata;
}

inline void recvprop::setextradata(const void *pdata)
{
	this->pextradata = pdata;
}

inline const char* recvprop::getparentarraypropname()
{
	return this->pparentarraypropname;
}

inline void    recvprop::setparentarraypropname(const char *parraypropname)
{
	this->pparentarraypropname = parraypropname;
}

namespace sdk::classes
{
	enum send_prop_type : int
	{
		dpt_int = 0,
		dpt_float,
		dpt_vector,
		dpt_vectorxy,
		dpt_string,
		dpt_array,
		dpt_datatable,
		dpt_int64,
		dpt_numsendproptypes
	};

	struct dvariant
	{
		union
		{
			float data_float;
			long data_int;
			char *data_string;
			void *data_ptr;
			float data_vector[3];
			__int64 data_int64;
		};

		int type;
	};

	struct recv_prop;
	struct recv_table;

	struct recv_proxy_data
	{
		const recv_prop *recv_prop_ptr;
		dvariant value;
		int element;
		int object_id;
	};

	struct recv_prop
	{
		using recv_var_proxy = void(__cdecl*)(const recv_proxy_data *, void *, void *);

		char *name;
		send_prop_type type;
		int flags;

		int str_buffer_size;
		bool in_array;
		const void *extra_data;

		recv_prop *array_prop;
		void *array_len_proxy;

		recv_var_proxy recv_var_proxy_fn;
		void *data_table_proxy_fn;
		recv_table *data_table;

		int offset;
		int element_stride;
		int num_elements;
		const char *parent_array_prop_name;
	};

	struct recv_table
	{
		recv_prop *props;
		int num_props;

		void *decoder;
		char *net_table_name;

		bool initialized;
		bool in_main_list;
	};
}