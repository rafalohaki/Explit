#pragma once
#include "i_handle_entity.hpp"

#define num_ent_entry_bits         (11 + 2)
#define num_ent_entries            (1 << num_ent_entry_bits)
#define invalid_ehandle_index       0xffffffff
#define num_serial_num_bits        16 // (32 - num_ent_entry_bits)
#define num_serial_num_shift_bits (32 - num_serial_num_bits)
#define ent_entry_mask             (( 1 << num_serial_num_bits) - 1)

class i_handle_entity;

class c_base_handle
{
public:
	c_base_handle();
	c_base_handle(const c_base_handle &other);
	c_base_handle(unsigned long value);
	c_base_handle(int ientry, int iserialnumber);

	void init(int ientry, int iserialnumber);
	void term();

	// even if this returns true, get() still can return return a non-null value.
	// this just tells if the handle has been initted with any values.
	bool isvalid() const;

	int getentryindex() const;
	int getserialnumber() const;

	int toint() const;
	bool operator !=(const c_base_handle &other) const;
	bool operator ==(const c_base_handle &other) const;
	bool operator ==(const i_handle_entity* pent) const;
	bool operator !=(const i_handle_entity* pent) const;
	bool operator <(const c_base_handle &other) const;
	bool operator <(const i_handle_entity* pent) const;

	// assign a value to the handle.
	const c_base_handle& operator=(const i_handle_entity *pentity);
	const c_base_handle& set(const i_handle_entity *pentity);

	// use this to dereference the handle.
	// note: this is implemented in game code (ehandle.h)
	i_handle_entity* get() const;

protected:
	// the low num_serial_bits hold the index. if this value is less than max_edicts, then the entity is networkable.
	// the high num_serial_num_bits bits are the serial number.
	unsigned long	m_index;
};

inline c_base_handle::c_base_handle()
{
	m_index = invalid_ehandle_index;
}

inline c_base_handle::c_base_handle(const c_base_handle &other)
{
	m_index = other.m_index;
}

inline c_base_handle::c_base_handle(unsigned long value)
{
	m_index = value;
}

inline c_base_handle::c_base_handle(int ientry, int iserialnumber)
{
	init(ientry, iserialnumber);
}

inline void c_base_handle::init(int ientry, int iserialnumber)
{
	m_index = ientry | (iserialnumber << num_ent_entry_bits);
}

inline void c_base_handle::term()
{
	m_index = invalid_ehandle_index;
}

inline bool c_base_handle::isvalid() const
{
	return m_index != invalid_ehandle_index;
}

inline int c_base_handle::getentryindex() const
{
	return m_index & ent_entry_mask;
}

inline int c_base_handle::getserialnumber() const
{
	return m_index >> num_ent_entry_bits;
}

inline int c_base_handle::toint() const
{
	return (int)m_index;
}

inline bool c_base_handle::operator !=(const c_base_handle &other) const
{
	return m_index != other.m_index;
}

inline bool c_base_handle::operator ==(const c_base_handle &other) const
{
	return m_index == other.m_index;
}

inline bool c_base_handle::operator ==(const i_handle_entity* pent) const
{
	return get() == pent;
}

inline bool c_base_handle::operator !=(const i_handle_entity* pent) const
{
	return get() != pent;
}

inline bool c_base_handle::operator <(const c_base_handle &other) const
{
	return m_index < other.m_index;
}

inline bool c_base_handle::operator <(const i_handle_entity *pentity) const
{
	unsigned long otherindex = (pentity) ? pentity->get_ref_ehandle().m_index : invalid_ehandle_index;
	return m_index < otherindex;
}

inline const c_base_handle& c_base_handle::operator=(const i_handle_entity *pentity)
{
	return set(pentity);
}

inline const c_base_handle& c_base_handle::set(const i_handle_entity *pentity)
{
	if (pentity) {
		*this = pentity->get_ref_ehandle();
	}
	else {
		m_index = invalid_ehandle_index;
	}

	return *this;
}