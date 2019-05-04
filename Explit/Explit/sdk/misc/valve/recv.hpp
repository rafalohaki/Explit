#pragma once

typedef enum
{
	dpt_int = 0,
	dpt_float,
	dpt_vector,
	dpt_vectorxy,
	dpt_string,
	dpt_array,
	dpt_data_table,
	dpt_int64,
	dpt_numsendproptypes
} sendproptype;

class recvprop;
class recvtable;
class dvariant;

// this is passed into recvproxy functions.
class crecvproxydata;

//-----------------------------------------------------------------------------
// pstruct = the base structure of the data_table this variable is in (like c_base_entity)
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


// note: data_table receive proxies work differently than the other proxies.
// pdata points at the object + the recv table's offset.
// pout should be set to the location of the object to unpack the data table into.
// if the parent object just contains the child object, the default proxy just does *pout = pdata.
// if the parent object points at the child object, you need to dereference the pointer here.
// note: don't ever return null from a data_table receive proxy function. bad things will happen.
typedef void(*data_tablerecvvarproxyfn)(const recvprop *pprop, void **pout, void *pdata, int objectid);

class recvprop
{
	// this info comes from the receive data table.
public:
	recvprop();

	void                        init_array(int nelements, int element_stride);

	int                         get_num_elements() const;
	void                        set_num_elements(int nelements);

	int                         get_element_stride() const;
	void                        set_element_stride(int stride);

	int                         getflags() const;

	const char*                 get_name() const;
	sendproptype                get_type() const;

	recvtable*                  get_data_table() const;
	void                        set_data_table(recvtable *ptable);

	recvvarproxyfn              get_proxy_fn() const;
	void                        set_proxy_fn(recvvarproxyfn fn);

	data_tablerecvvarproxyfn     get_data_table_proxy_fn() const;
	void                        set_data_table_proxy_fn(data_tablerecvvarproxyfn fn);

	int                         get_offset() const;
	void                        set_offset(int o);

	// arrays only.
	recvprop*                   get_array_prop() const;
	void                        set_array_prop(recvprop *pprop);

	// arrays only.
	void                        set_array_length_proxy(arraylengthrecvproxyfn proxy);
	arraylengthrecvproxyfn      get_array_length_proxy() const;

	bool                        is_inside_array() const;
	void                        set_inside_array();

	// some property types bind more data to the prop in here.
	const void*                 get_extra_data() const;
	void                        set_extra_data(const void *pdata);

	// if it's one of the numbered "000", "001", etc properties in an array, then
	// these can be used to get its array property name for debugging.
	const char*                 get_parent_array_prop_name();
	void                        set_parent_array_prop_name(const char *parraypropname);

public:

	const char                  *pvarname;
	sendproptype                recvtype;
	int                         flags;
	int                         string_buffer_size;


public:

	bool                        binside_array;        // set to true by the engine if this property sits inside an array.

												   // extra data that certain special property types bind to the property here.
	const void *pextra_data;

	// if this is an array (dpt_array).
	recvprop                    *parray_prop;
	arraylengthrecvproxyfn      array_length_proxy;

	recvvarproxyfn              proxy_fn;
	data_tablerecvvarproxyfn     data_table_proxy_fn;    // for rdt_data_table.

	recvtable                   *pdata_table;        // for rdt_data_table.
	int                         offset;

	int                         element_stride;
	int                         nelements;

	// if it's one of the numbered "000", "001", etc properties in an array, then
	// these can be used to get its array property name for debugging.
	const char                  *pparent_array_prop_name;
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

	int                 get_num_props();
	recvprop*           get_prop(int i);

	const char*         get_name();

	// used by the engine while initializing array props.
	void                set_initialized(bool binitialized);
	bool                is_initialized() const;

	// used by the engine.
	void                set_in_main_list(bool binlist);
	bool                is_in_main_list() const;


public:

	// properties described in a table.
	recvprop           *pprops;
	int                 nprops;

	// the decoder. note: this covers each recvtable and all its children (ie: its children
	// will have their own decoders that include props for all their children).
	crecvdecoder       *pdecoder;

	const char         *pnet_table_name;    // the name matched between client and server.


private:

	bool                binitialized;
	bool                bin_main_list;
};



inline int recvtable::get_num_props()
{
	return this->nprops;
}

inline recvprop* recvtable::get_prop(int i)
{
	return &this->pprops[i];
}

inline const char* recvtable::get_name()
{
	return this->pnet_table_name;
}

inline void recvtable::set_initialized(bool binitialized)
{
	this->binitialized = binitialized;
}

inline bool recvtable::is_initialized() const
{
	return this->binitialized;
}

inline void recvtable::set_in_main_list(bool binlist)
{
	this->bin_main_list = binlist;
}

inline bool recvtable::is_in_main_list() const
{
	return this->bin_main_list;
}


inline void recvprop::init_array(int nelements, int element_stride)
{
	this->recvtype = dpt_array;
	this->nelements = nelements;
	this->element_stride = element_stride;
}

inline int recvprop::get_num_elements() const
{
	return this->nelements;
}

inline void recvprop::set_num_elements(int nelements)
{
	this->nelements = nelements;
}

inline int recvprop::get_element_stride() const
{
	return this->element_stride;
}

inline void recvprop::set_element_stride(int stride)
{
	this->element_stride = stride;
}

inline int recvprop::getflags() const
{
	return this->flags;
}

inline const char* recvprop::get_name() const
{
	return this->pvarname;
}

inline sendproptype recvprop::get_type() const
{
	return this->recvtype;
}

inline recvtable* recvprop::get_data_table() const
{
	return this->pdata_table;
}

inline void recvprop::set_data_table(recvtable *ptable)
{
	this->pdata_table = ptable;
}

inline recvvarproxyfn recvprop::get_proxy_fn() const
{
	return this->proxy_fn;
}

inline void recvprop::set_proxy_fn(recvvarproxyfn fn)
{
	this->proxy_fn = fn;
}

inline data_tablerecvvarproxyfn recvprop::get_data_table_proxy_fn() const
{
	return this->data_table_proxy_fn;
}

inline void recvprop::set_data_table_proxy_fn(data_tablerecvvarproxyfn fn)
{
	this->data_table_proxy_fn = fn;
}

inline int recvprop::get_offset() const
{
	return this->offset;
}

inline void recvprop::set_offset(int o)
{
	this->offset = o;
}

inline recvprop* recvprop::get_array_prop() const
{
	return this->parray_prop;
}

inline void recvprop::set_array_prop(recvprop *pprop)
{
	this->parray_prop = pprop;
}

inline void recvprop::set_array_length_proxy(arraylengthrecvproxyfn proxy)
{
	this->array_length_proxy = proxy;
}

inline arraylengthrecvproxyfn recvprop::get_array_length_proxy() const
{
	return this->array_length_proxy;
}

inline bool recvprop::is_inside_array() const
{
	return this->binside_array;
}

inline void recvprop::set_inside_array()
{
	this->binside_array = true;
}

inline const void* recvprop::get_extra_data() const
{
	return this->pextra_data;
}

inline void recvprop::set_extra_data(const void *pdata)
{
	this->pextra_data = pdata;
}

inline const char* recvprop::get_parent_array_prop_name()
{
	return this->pparent_array_prop_name;
}

inline void    recvprop::set_parent_array_prop_name(const char *parraypropname)
{
	this->pparent_array_prop_name = parraypropname;
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
		dpt_data_table,
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