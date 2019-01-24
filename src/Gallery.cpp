#ifndef CNBIDRAW_GALLERY_CPP
#define CNBIDRAW_GALLERY_CPP

#include "Gallery.hpp"

namespace cnbi {
    namespace draw {

Gallery::Gallery(float width, float height) : Image(width, height) {}


Gallery::~Gallery(void) {
}


bool Gallery::SetFolder(const std::string& folder, const std::vector<std::string> exts) {



	DIR* dir = opendir(folder.c_str());

	if(!dir) {
		return false;
	}

	std::lock_guard<std::mutex> lock(this->shp_mutex_);
	this->WaitShape();
	dirent* entry;
	while((entry = readdir(dir)) != nullptr) {
		for(auto it=exts.begin(); it!=exts.end(); ++it) {
			if(this->HasExtension(entry->d_name, *it)) {
				this->list_.push_back(entry->d_name);
			}
		}
	}

	closedir(dir);
	
	std::sort(this->list_.begin(), this->list_.end());
	this->current_ = this->Begin();
	this->folder_  = folder;
	this->PostShape();

	this->Select();

	return true;
}

size_t Gallery::Size(void) {
	return this->list_.size();
}

bool Gallery::HasExtension(const std::string& name, const std::string& ext) {

	bool result = false;
	result = (name.size() >= ext.size()) && std::equal(ext.rbegin(), ext.rend(), name.rbegin());
	return result;

}


bool Gallery::Next(void) {
	bool result = false;
	if(this->current_ != this->End()) {
		this->current_++;
		result = true;
	}
	return result;
}

bool Gallery::Previous(void) {
	bool result = false;
	if(this->current_ != this->Begin()) {
		this->current_--;
		result = true;
	}
	return result;
}

bool Gallery::Rewind(void) {
	this->current_ = this->Begin();
	return true;
}

bool Gallery::GoTo(GalleryIt it) {
	this->current_ = it;
	return true;
}

GalleryIt Gallery::Current(void) {
	return this->current_;
}


GalleryIt Gallery::Begin(void) {
	return this->list_.begin();
}

GalleryIt Gallery::End(void) {
	return this->list_.end();
}

bool Gallery::Select(GalleryIt it) {
	bool result;
	std::string filepath;
	
	if(it >= this->End())
		return false;

	filepath = this->folder_ + "/" + (*it);
	result = this->Set(filepath, 6);
	
	if(result == true) {
		this->CreateFill();
		this->CreateStroke();
		this->Create();
	}
	return result;
}

bool Gallery::Select(void) {
	return this->Select(this->current_);
}

bool Gallery::Select(unsigned int id) {
	GalleryIt it = this->Begin() + id;
	return this->Select(it);
}


	}
}

#endif
