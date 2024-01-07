//Generic template for loading resources in a Map container where the Key is an ID and the Value is the corresponding Resource type( Texture, Font etc.) (different implemntation for music theme since thats streaming)

#ifndef RESOURCEHOLDER_H
#define RESOURCEHOLDER_H

#include <string>
#include <map>
#include <memory>
#include <stdexcept>

template<typename Resource, typename Identifier>
class ResourceHolder{
public:
    void load(Identifier, const std::string& filename);

    template<typename Parameter> //overload func for second parameters
    void load(Identifier, const std::string& filename, Parameter& secondParam);

    Resource& get (Identifier id);
    const Resource& get (Identifier id) const; // const qualified overload (if texture is const)

private:
    // if the map goes out of scope everything is deallocated inside it by the unique_ptr
    std::map<Identifier, std::unique_ptr<Resource>> mResourceMap; // dictonary key (texture enum) - value (unique_ptr to the texture itself)
    

};

template<typename Resource, typename Identifier>
void ResourceHolder<Resource,Identifier>::load(Identifier id, const std::string& filename){

    std::unique_ptr<Resource> resource(new Resource()); // store texture in unique_ptr

    if (!resource->loadFromFile(filename)) {//load it from the file and check it
        throw std::runtime_error("TextureHolder::Load - Failed to load the file " + filename);
    }
    auto inserted = mResourceMap.insert(std::make_pair(id, std::move(resource))); // insert it into the map
    //returns pair! an iterator to the element and a boolean value if it was succesful
    assert(inserted.second); //if 2 of the same texture is loaded with the same ID

}

template<typename Resource, typename Identifier>
template<typename Parameter>
void ResourceHolder<Resource,Identifier>::load(Identifier id, const std::string& filename, Parameter& secondParam){

    std::unique_ptr<Resource> resource(new Resource()); // store texture in unique_ptr

    if (!resource->loadFromFile(filename, secondParam)) {//second paramter if shaders(fragment and vertex, sf:shader has func with theese 2 params) or texture with second param
        throw std::runtime_error("TextureHolder::Load - Failed to load the file " + filename);
    }
    auto inserted = mResourceMap.insert(std::make_pair(id, std::move(resource))); // insert it into the map
    //returns pair! an iterator to the element and a boolean value if it was succesful
    assert(inserted.second); //if 2 of the same texture is loaded with the same ID

}


template<typename Resource, typename Identifier>
Resource& ResourceHolder<Resource,Identifier>::get (Identifier id){

    //auto deduces the correct type at intializtation
    auto found = mResourceMap.find(id); //returns an iterator if found , if not end() iterator
    assert(found != mResourceMap.end());//if texture is queried before loaded
    return *found->second; // return the second element, the value
}

template<typename Resource, typename Identifier>
const Resource& ResourceHolder<Resource,Identifier>::get (Identifier id) const{
    auto found = mResourceMap.find(id);
    return *found->second;
}


#endif  //RESOURCEHOLDER_H