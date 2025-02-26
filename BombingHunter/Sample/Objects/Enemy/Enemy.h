#pragma once

#include "../GameObject.h"

class Enemy : public GameObject
{
private:
	int animation[2];					//�A�j���[�V�����摜
	int animation_count;		//�A�j���[�V��������
	Vector2D direction;					//�i�s����

public:
	Enemy();
	~Enemy();

	void Initialize() override;				//����������
	void Update() override;					//�X�V����
	void Draw() const override;				//�`�揈��
	void Finalize() override;				//�I������

	//�����蔻��ʒm����
	virtual void OnHitCollision(GameObject* hit_object) override;

private:
	//�ړ�����
	void Movement();
	//�A�j���[�V��������
	void AnimationControl();

};