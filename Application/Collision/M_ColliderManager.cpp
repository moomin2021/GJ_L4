#include "M_ColliderManager.h"
#include "M_RectCollider.h"
#include "M_CircleCollider.h"
#include "CollisionChecker.h"

void M_ColliderManager::Update(void)
{
    // callback実行用の配列を初期化
    colliders_executeCallback_.clear();
    if (is_active_ == false) { return; }

    // フラグやptrの更新処理なので、衝突検知と分けて行う。
    for (const auto& collider : colliders_)
    {
        // 1.衝突フラグやコライダーptrの保存と、それらの初期化
        collider->Execute_UpdateColFlags();
    }

    // 衝突検知
    for (auto it1 = colliders_.begin(); it1 != colliders_.end(); ++it1)
    {
        // コライダーが有効になっているか
        if ((*it1)->Get_IsActive() == false) { continue; }


        // it1の1つ先のイテレータ
        auto it2 = it1;
        it2++;
        // ++it1 ~ colliders_.end()までを全検索
        for (; it2 != colliders_.end(); ++it2)
        {
            // コライダーが有効になっているか
            if ((*it2)->Get_IsActive() == false) { continue; }

            // 2.it1とit2の衝突判定を確認
            // 3.衝突判定フラグや接触相手のptrを取得
            Collision(*it1, *it2);
        }

        // 4.callbackを実行するコライダーを記録
        colliders_executeCallback_.push_back(it1);
    }

    // �R�[���o�b�N�̎��s
    for (auto& it : colliders_executeCallback_)
    {
        // まとめて実行する
        (*it)->Execute_Callback();
    }
}

void M_ColliderManager::Register(ICollider* arg_collider)
{
    // Id�̊��蓖��
    arg_collider->id_ = countId_;
    // ���p��Id�����炷
    countId_++;

    // ���X�g�ɓo�^
    colliders_.push_back(arg_collider);
}

void M_ColliderManager::Collision(ICollider* arg_col1, ICollider* arg_col2)
{
    bool isCol = false;
    bool temp = false;

    // ��`�Ƌ�`
    temp = Rect2Rect(arg_col1, arg_col2);
    isCol = (std::max)(isCol, temp);        // true��false�ɏ��������Ȃ��悤��
    // ��`�Ɖ~
    temp = Rect2Circle(arg_col1, arg_col2);
    isCol = (std::max)(isCol, temp);        // true��false�ɏ��������Ȃ��悤��

    if (!isCol) { return; }

    // �Փ˔���t���O��ڐG�����ptr���擾
    arg_col1->Set_IsCol(true);
    arg_col1->Record_Collider(arg_col2);

    arg_col2->Set_IsCol(true);
    arg_col2->Record_Collider(arg_col1);
}

bool M_ColliderManager::Rect2Rect(ICollider* arg_col1, ICollider* arg_col2)
{
    bool isCorrectShape = (arg_col1->Get_Shape() == SHAPE_RECT) && (arg_col2->Get_Shape() == SHAPE_RECT);
    if (!isCorrectShape) { return false; }

    M_RectCollider* rect1 = static_cast<M_RectCollider*>(arg_col1);
    M_RectCollider* rect2 = static_cast<M_RectCollider*>(arg_col2);

    bool isCol = CollisionChecker::Check_OBB2OBB(rect1->square_, rect2->square_);
    return isCol;
}

bool M_ColliderManager::Rect2Circle(ICollider* arg_col1, ICollider* arg_col2)
{
    bool isCorrectShape1 = (arg_col1->Get_Shape() == SHAPE_RECT) && (arg_col2->Get_Shape() == SHAPE_CIRCLE);
    bool isCorrectShape2 = (arg_col1->Get_Shape() == SHAPE_CIRCLE) && (arg_col2->Get_Shape() == SHAPE_RECT);
    // �ǂ����false�Ȃ�A�֐��X�L�b�v
    if (!isCorrectShape1 && !isCorrectShape2) { return false; }

    if (isCorrectShape1)
    {
        M_RectCollider* rect = static_cast<M_RectCollider*>(arg_col1);
        M_CircleCollider* circle = static_cast<M_CircleCollider*>(arg_col2);

        return CollisionChecker::Check_OBB2Circle(rect->square_, circle->circle_);
    }
    else
    {
        M_CircleCollider* circle = static_cast<M_CircleCollider*>(arg_col1);
        M_RectCollider* rect = static_cast<M_RectCollider*>(arg_col2);

        return CollisionChecker::Check_OBB2Circle(rect->square_, circle->circle_);
    }
}
