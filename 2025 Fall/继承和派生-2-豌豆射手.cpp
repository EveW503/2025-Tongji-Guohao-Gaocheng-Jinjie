#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <cstring>
#include <limits>
#define LAWN_LENGTH 9
#define SUNLIGHT_TIME 3
#define TARGET_DAMAGE 500
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
PlantBase::PlantBase(int hp, int cost):hp(hp), cost(cost),plant_time(0),name(nullptr)
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
class PeaShooter:public PlantBase {
private:
protected:
public:
	PeaShooter(int hp, int cost, time_t plant_time);
	void plantPea(int& sunlight, int& plant_num, PeaShooter* lawn[], time_t current);
	void peaAttack(int& damage, time_t current);
	time_t getTime();
};

PeaShooter::PeaShooter(int hp, int cost, time_t plant_time_in) : PlantBase(60, 100) 
{
	plant_time = plant_time_in;
}

void PeaShooter::plantPea(int& sunlight, int& plant_num, PeaShooter* lawn[],time_t current)
{
	if (sunlight >= cost && plant_num < 9)
	{
		sunlight = sunlight - cost;
		plant_num = plant_num + 1;
		lawn[plant_num - 1] = new PeaShooter(60, 100, current);
		cout << "请为植物命名" << endl;
	}
}

time_t PeaShooter::getTime()
{
	return plant_time;
}

void PeaShooter::peaAttack(int& damage, time_t current)
{
	if((current - plant_time)%2 == 0)
	    damage = damage + ATTACK_DAMAGE;
}
/********************************************/


int main()
{
	/* 变量声明 */
	int plant_num = 0; // 记录存活植物总数
	PeaShooter* lawn[LAWN_LENGTH] = {};
	time_t record_plant_time[100] = { 0 };
	int plant_num_all = 0;

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
		for (int i = 0; i < plant_num; i++)
		{
			lawn[i]->peaAttack(damage, current);
		}

		/* 3. 玩家：放植物（一次只能放一株）*/
		if (sunlight >= 100 && plant_num < 9)
		{
			plant_num = plant_num + 1;
			plant_num_all = plant_num_all + 1;
			lawn[plant_num - 1] = new PeaShooter(60, 100, current);
			record_plant_time[plant_num_all - 1] = current;
			sunlight = sunlight - 100;
		}

		/* 4. 僵尸：从第n秒开始，每一秒最右侧的植物会收到10*(current-n)的伤害 */
		if (current >= n && plant_num > 0)
		{
			int damage_zombie = static_cast<int>(10 * (current - n));
			if (lawn[plant_num - 1]->hurt(damage_zombie))
			{
				delete lawn[plant_num - 1];
				lawn[plant_num - 1] = nullptr;

				plant_num = plant_num - 1;
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
	cout << "每一株植物种下的时刻：" << endl;
	for (int i = 0; i < plant_num_all; i++)
	{
		cout << record_plant_time[i] << endl;
	}

	cout << "幸存植物的名字：" << endl;
	for (int i = 0; i < plant_num; i++)
	{
		char* temp_name_ptr = nullptr;
		temp_name_ptr = lawn[i]->get_name();
		cout << temp_name_ptr << endl;
	}

	for (int i = 0; i < plant_num; i++)
	{
		if (lawn[i] != nullptr)
		{
			delete lawn[i]; // <--- 修改：手动释放剩余的植物对象
			lawn[i] = nullptr;
		}
	}

	return 0;
}