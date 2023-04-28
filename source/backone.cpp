#include "backone.h"

#include"libs/scene.h"
#include"movebox.h"
#include"player.h"

BackOne::BackOne(Scene* sc)
	:Object			(sc)
	,playerPosList	()
	,boxPosList		()
	,playerDirList	()
{}
BackOne::~BackOne(){
}
void BackOne::Init() {

	Reset();

	MoveBox* moveBox = GetScene()->Invoke<MoveBox>();
	if (!CheckClass<MoveBox>())
		return;

	const int mIndex = moveBox->GetMaxIndex();
	boxPosList.resize(mIndex);
}
void BackOne::Update(){
	//‰ŠúˆÊ’u‚ª–³‚¢‚È‚çæ“¾
	FastPos();
	//‹L˜^ãŒÀ
	Limit();

}
void BackOne::Draw(){
}



void BackOne::Reset(){
	Vec2 playerPos = *(playerPosList.begin());
	int playerDir = *(playerDirList.begin());
	std::vector<Vec2>boxPos;
	for (int i = 0; static_cast<unsigned int>(i) < boxPosList.size(); i++) {
		auto it = boxPosList[i].begin();
		boxPos.emplace_back(*(it));
		boxPosList[i].clear();
	}

	playerPosList.clear();
	playerDirList.clear();

	playerPosList.emplace_back(playerPos);
	playerDirList.emplace_back(playerDir);
	for (int i = 0; static_cast<unsigned int>(i) < boxPosList.size(); i++) {
		boxPosList[i].emplace_back(boxPos[i]);
	}
}

void BackOne::PushToPlayer(int _dir, Vec2 _pos){
	playerPosList.emplace_back(_pos	);
	playerDirList.emplace_back(_dir	);
}

void BackOne::PushToBoxPos(int _index,Vec2 _pos){
	boxPosList[_index].emplace_back(_pos);
}

Vec2 BackOne::GetToPlayerPos(){
	if (playerPosList.empty())
		return Vec2();
	
	auto it		= playerPosList.end();
	it--;
	Vec2 ans	= (*it);

	auto it2	= playerPosList.begin();
	it2++;
	
	if (it != it2)
		playerPosList.erase(it);

	return ans;
}

int BackOne::GetToPlayerDir(){
	if (playerPosList.empty())
		return 0;

	auto it = playerDirList.end();
	it--;
	int ans = (*it);

	auto it2 = playerDirList.begin();
	it2++;

	if (it != it2)
		playerDirList.erase(it);

	return ans;
}

Vec2 BackOne::GetToBoxPos(int _index){
	if (boxPosList[_index].empty())
		return Vec2();

	auto it = boxPosList[_index].end();
	it--;
	Vec2 ans = (*it);

	auto it2 = boxPosList[_index].begin();
	it2++;

	if(it!=it2)
		boxPosList[_index].erase(it);

	return ans;
}

void BackOne::FastPos(){
	if (playerPosList.empty()) {


	Player* p = GetScene()->Invoke<Player>();
	if (CheckClass<Player>())
		PushToPlayer(0, p->GetPos());
	
	MoveBox* mb = GetScene()->Invoke<MoveBox>();
	if (CheckClass<MoveBox>()) 
		mb->PushPoss();
	}

	
}

void BackOne::Limit() {
	int indexNum = playerPosList.size();
	if (indexNum < 20)
		return;

	MoveBox* moveBox = GetScene()->Invoke<MoveBox>();
	if (!CheckClass<MoveBox>())
		return;

	const int mIndex = moveBox->GetMaxIndex();

	while (true) {
		if (indexNum < 20) 
			return;
		
		auto it_pos= playerPosList.begin();
		it_pos++;
		playerPosList.erase(it_pos);

		auto it_dir = playerDirList.begin();
		it_dir++;
		playerDirList.erase(it_dir);

		for (int i = 0; i < mIndex; i++) {
			auto it_box = boxPosList[i].begin();
			it_box++;
			boxPosList[i].erase(it_box);
		}


		indexNum = playerPosList.size();
	}
}
