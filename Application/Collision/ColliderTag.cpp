#include "ColliderTag.h"

bool ColliderTag::Tag_Search(const std::string& arg_tagName)
{
    for (const auto& tag : tags_)
    {
        if (tag == arg_tagName) { return true; }
    }

    // �݂���Ȃ�����
    return false;
}
