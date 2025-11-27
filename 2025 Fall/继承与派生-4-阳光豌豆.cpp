#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <cstring>
#define LAWN_LENGTH 9
#define SUNLIGHT_TIME 3
#define TARGET_DAMAGE 1000
#define ATTACK_DAMAGE 10
using namespace std;

time_t current = 0;  // 模拟记录时间，单位s

/*************将基类的声明拷贝至此**************/
class PlantBase {
private:
	int hp;			// 植物的生命值
	char* name;		// 植物的名字（长度不超过20）

protected:
	int cost;		// 种植花费的阳光
	time_t plant_time;	// 植物被种下的时间

public:
	PlantBase(int hp, int cost);
	~PlantBase();
	bool hurt(int damage);
	char* get_name();
};
/********************************************/


/*************在这里给出基类的实现**************/
PlantBase::PlantBase(int hp, int cost) :hp(hp), cost(cost), plant_time(0), name(nullptr)
{
	char temp_name[21] = { 0 };

	while (cin.peek() == '\n')
	{
		cin.ignore();
	}
	cin.getline(temp_name, 20);
	name = new char[strlen(temp_name) + 1];
	if (name == NULL)
	{
		cout << "为name分配空间失败！" << endl;
		exit(EXIT_FAILURE);
	}
	strcpy(name, temp_name);
}

PlantBase::~PlantBase()
{
	delete[] name;
	name = nullptr;
}

bool PlantBase::hurt(int damage)  //死亡返回true，没死返回false
{
	if (hp <= 0)
		return true;
	else
	{
		hp = hp - damage;
		if (hp <= 0)
			return true;
		else
			return false;
	}
}

char* PlantBase::get_name()
{
	return name;
}



/********************************************/


/**********在这里给出派生类的声明和实现***********/
class SunFlower : virtual public PlantBase {
private:
protected:
public:
	SunFlower(time_t plant_time, int hp);
	void createSunlight(int& sunlight, time_t current);
};

SunFlower::SunFlower(time_t plant_time_in, int hp) :PlantBase(60, 5)
{
	plant_time = plant_time_in;
}

void SunFlower::createSunlight(int& sunlight, time_t current)
{
	if ((current - plant_time) % 5 == 0)
	{
		sunlight = sunlight + 25;
	}
}

class PeaShooter :virtual public PlantBase {
private:
protected:
public:
	PeaShooter(int hp, int cost, time_t plant_time);
	void peaAttack(int& damage, time_t current);
	time_t getTime();
};

PeaShooter::PeaShooter(int hp, int cost, time_t plant_time_in) : PlantBase(60, 100)
{
	plant_time = plant_time_in;
}

time_t PeaShooter::getTime()
{
	return plant_time;
}

void PeaShooter::peaAttack(int& damage, time_t current)
{
	if ((current - plant_time) % 2 == 0)
		damage = damage + ATTACK_DAMAGE;
}	

class SunnyPea : public PeaShooter, public SunFlower {
private:
protected:
public:
	SunnyPea(int hp, int cost, time_t current) :PlantBase(hp, cost), PeaShooter(hp, cost, current), SunFlower(current, hp)
	{
	};
};

/********************************************/


int main()
{
	/* 变量声明 */
	int plant_num = 0; // 记录植物总数
	SunnyPea* lawn[LAWN_LENGTH] = { nullptr };	

	time_t history_times[1000];                    // 记录种植历史
	int history_count = 0;


	// 输入数据
	int sunlight, damage;
	damage = 0;
	time_t n;
	cin >> sunlight >> n;

	while (true) {
		// 1. 环境：每3/6/9/...s掉落一个25的阳光
		if (current % SUNLIGHT_TIME == 0 && current > 0) {
			sunlight += 25;
		}

		/* 2. 植物：发动攻击 */
		for (int i = 0; i < LAWN_LENGTH; i++) {
			if (lawn[i] != nullptr) {
				((SunnyPea*)lawn[i])->peaAttack(damage, current);
				((SunnyPea*)lawn[i])->createSunlight(sunlight, current);
			}
		}


		/* 3. 玩家：放植物（一次只能放一株）*/
		bool is_empty = false;
		int empty_index = -1;
		for (int i = 0; i < LAWN_LENGTH; i++)
		{
			if (lawn[i] == nullptr)
			{
				is_empty = true;
				empty_index = i;
				break;
			}
		}

		if (sunlight >= 125)
		{
			if (is_empty)
			{
				lawn[empty_index] = new SunnyPea(60, 125, current);
				is_empty = false;
				plant_num = plant_num + 1;
				sunlight = sunlight - 125;
				if (history_count < 1000) history_times[history_count++] = current;
			}
		}


		/* 4. 僵尸：从第n秒开始，每一秒最右侧的植物会收到10*(current-n)的伤害 */
		if (current >= n) {
			int rightmost_idx = -1;
			for (int i = LAWN_LENGTH - 1; i >= 0; i--) {
				if (lawn[i] != nullptr) {
					rightmost_idx = i;
					break;
				}
			}

			if (rightmost_idx != -1) {
				int zombie_damage = 10 * static_cast<int>((current - n));
				bool is_dead = lawn[rightmost_idx]->hurt(zombie_damage);
				if (is_dead) {
					delete lawn[rightmost_idx];
					lawn[rightmost_idx] = nullptr;
					plant_num--;
				}
			}
		}


		// 5. 游戏胜利/失败判断
		if (damage >= TARGET_DAMAGE) {
			cout << "游戏胜利" << endl;
			break;
		}
		else if (current >= n && plant_num == 0) {  // 提前判定失败
			cout << "游戏失败" << endl;
			break;
		}
		else if (current >= 100) {  // 如果第100秒过去仍未积累足够阳光，则判负
			cout << "游戏失败" << endl;
			break;
		}

		current++;
	}

	cout << "时刻数：" << current << " 阳光数：" << sunlight << " 植物数：" << plant_num << endl;

	/* 其他输出与内存回收 */

	if (history_count > 0) {
		cout << endl << "每一株植物种下的时刻：" << endl;
		for (int i = 0; i < history_count; i++) {
			cout << history_times[i] << (i == history_count - 1 ? "" : " ");
		}
		cout << endl;
	}

	if (plant_num > 0) {
		cout << endl << "幸存植物的名字：" << endl;
		for (int i = 0; i < LAWN_LENGTH; i++) {
			if (lawn[i] != nullptr) {
				cout << lawn[i]->get_name() << endl;
			}
		}
	}

	for (int i = 0; i < LAWN_LENGTH; i++) {
		if (lawn[i]) delete lawn[i];
	}

	return 0;
}