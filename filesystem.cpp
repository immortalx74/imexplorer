#pragma once

#include "app.h"

FSRecordCollection::FSRecordCollection(std::string label, size_t init_capacity)
{
	this->fs_records.Reserve(init_capacity);
	this->label = label;

	FSRCTabs.tabs.Push(this);
}