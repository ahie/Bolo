#pragma once
enum DamageType { AOE_DAMAGE, SINGLE_TARGET_DAMAGE };

struct Projectile
{
	float speed_;
	float size_;
};

class AttackHandler
{
public:
	void newMeleeDamageEvent(DamageType, float);
	void newProjectile(Projectile,DamageType,float);
private:
};

class Attack
{
public:
	virtual void attack() = 0;
protected:
	float damage_;
	DamageType dmgType_;
	AttackHandler* handler_;
};

class MeleeAttack : public Attack
{
public:
	virtual void attack() {
		handler_->newMeleeDamageEvent(dmgType_, damage_);
	}
};

class RangedAttack : public Attack
{
public:
	virtual void attack() {
		handler_->newProjectile(projectile_, dmgType_, damage_);
	}
private:
	Projectile projectile_;
};