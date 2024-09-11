#pragma once
#include <list>
#include <string>

class ColliderTag
{
public:
    //>> �R���X�g���N�^
    ColliderTag(void) = default;
    ~ColliderTag(void) = default;

    //>> �֐�
    // �^�O|�ǉ�
    void Tag_Add(const std::string& arg_tagName) { tags_.push_back(arg_tagName); }
    // �^�O|�w��폜
    void Tag_Remove(const std::string& arg_tagName) { tags_.remove(arg_tagName); }
    // �^�O|�S�폜
    void Tag_Clear(void) { tags_.clear(); }
    // �^�O|���݌���
    bool Tag_IsExist(const std::string& arg_tagName) { return Tag_Search(arg_tagName); }

private:
    // �^�O|���݌����i�B���j
    bool Tag_Search(const std::string& arg_tagName);

    //>> �ϐ�
    std::list<std::string> tags_;
};

