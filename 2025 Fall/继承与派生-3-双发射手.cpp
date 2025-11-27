#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#define LAWN_LENGTH 9
#define SUNLIGHT_TIME 3
#define TARGET_DAMAGE 3000
#define REPEATER_ATTACK_DAMAGE 20
#define GATLING_ATTACK_DAMAGE 40
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
	PlantBase(PlantBase& base);	// 复制构造函数
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

PlantBase::PlantBase(PlantBase& base)
{
	hp = base.hp;
	cost = 0;
	plant_time = 0;

	name = new char[strlen(base.name) + 1];
	if (name == NULL)
	{
		cout << "为name分配空间失败！" << endl;
		exit(EXIT_FAILURE);
	}

	strcpy(name, base.name);
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
class Repeater :public PlantBase {
private:
protected:
public:
	Repeater(int hp, int cost, time_t plant_time);
	void reAttack(int& damage, time_t current);
	time_t getTime();
	int getCost();
};

class GatlingPea : public PlantBase {
private:
protected:
public:
	GatlingPea(PlantBase& rep, int cost, time_t plant_time);
	void gaAttack(int& damage, time_t current);
	time_t getTime();
	int getCost();
};

Repeater::Repeater(int hp, int cost, time_t plant_time_in) : PlantBase(60, 150)
{
	plant_time = plant_time_in;
}

time_t Repeater::getTime()
{
	return plant_time;
}

int Repeater::getCost()
{
	return cost;
}
void Repeater::reAttack(int& damage, time_t current)
{
	if ((current - plant_time) % 2 == 0)
		damage = damage + REPEATER_ATTACK_DAMAGE;
}

GatlingPea::GatlingPea(PlantBase& rep, int cost_in, time_t plant_time_in): PlantBase(rep)
{
	plant_time = plant_time_in;
	cost = cost_in;
}

void GatlingPea::gaAttack(int& damage, time_t current)
{
	if ((current - plant_time) % 2 == 0)
		damage = damage + GATLING_ATTACK_DAMAGE;
}	

time_t GatlingPea::getTime()
{
	return plant_time;
}

int GatlingPea::getCost()
{
	return cost;
}
/********************************************/

void plantRe(int& sunlight, int& plant_num_re, Repeater* lawn_re[], time_t current, int cost_re)
{
	if (sunlight >= 150 && plant_num_re < 9)
	{
		sunlight = sunlight - 150;
		plant_num_re = plant_num_re + 1;
		lawn_re[plant_num_re - 1] = new Repeater(60, 150, current);
		cout << "请为植物命名" << endl;
	}
}


int main()
{
	/* 变量声明 */ 
	int plant_num = 0;

	time_t history_times[1000];                    // 记录种植历史
	int history_count = 0;

	int cost_re = 150;
	int cost_ga = 150;

	PlantBase* lawn[LAWN_LENGTH] = { nullptr };
	int lawn_type[LAWN_LENGTH] = { 0 };

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
				if (lawn_type[i] == 1) {
					((Repeater*)lawn[i])->reAttack(damage,current);
				}
				else if (lawn_type[i] == 2) {
					((GatlingPea*)lawn[i])->gaAttack(damage,current);
				}
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

		if (sunlight >= 150)
		{
			if (is_empty)
			{
				lawn[empty_index] = new Repeater(60, 150, current);
				lawn_type[empty_index] = 1;
				is_empty = false;
				plant_num = plant_num + 1;
				sunlight = sunlight - 150;
				if (history_count < 1000) history_times[history_count++] = current;
			}
			else
			{
				int gat_index = -1;
				for (int i = 0; i < LAWN_LENGTH; i++)
				{
					if (lawn[i] != nullptr && lawn_type[i] == 1) 
					{
						gat_index = i;
						break;
					}
				}
				if (gat_index != -1)
				{
					PlantBase* old_plant = lawn[gat_index];
					lawn[gat_index] = new GatlingPea(*old_plant, cost_ga, current);
					lawn_type[gat_index] = 2;
					delete old_plant;
					sunlight = sunlight - 150;
					if (history_count < 1000) history_times[history_count++] = current;
				}

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
					lawn_type[rightmost_idx] = 0;
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
				if (lawn_type[i] == 1) cout << "Repeater: ";
				else if (lawn_type[i] == 2) cout << "Gatling: ";
				cout << lawn[i]->get_name() << endl;
			}
		}
	}

	for (int i = 0; i < LAWN_LENGTH; i++) {
		if (lawn[i]) delete lawn[i];
	}


	return 0;
}