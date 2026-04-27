#include <Include/Match3/MapMatch3.h>
#include <Engine.h>
#include <iostream>
#include <Include/BasicBox.h>

Match3::MapMatch3::MapMatch3()
{
	CreateComponent<MapUpdater>();
	CreateComponent<MapRender>();
}

void Match3::MapMatch3::InitMap()
{
	map.clear();
	for (int y = 0; y < mapWidth; y++) {
		for (int x = 0; x < mapHeight; x++) {
			map.push_back(CreateCandy(x, y));
		}
	}
}

void Match3::MapMatch3::Awake()
{
	InitMap();
}

Match3::Candy* Match3::MapMatch3::CreateCandy(int x, int y)
{
	int random = rand() % 5 + 1;
	switch (random) {
	case 1:
	{
		return MakeCandy(1, sf::Color::Red, x, y);
	}
	case 2:
	{
		return MakeCandy(2, sf::Color::Blue, x, y);
	}
	case 3:
	{
		return MakeCandy(3, sf::Color::Green, x, y);
	}
	case 4:
	{
		return MakeCandy(4, sf::Color::Yellow, x, y);
	}
	default:
		return nullptr;
	}
}

Match3::Candy* Match3::MapMatch3::MakeCandy(int i, sf::Color color, int x, int y)
{
	Candy* candy = new Candy(i);
	BasicBox* box = candy->CreateComponent<BasicBox>((float)mapTileSize, (float)mapTileSize);
	box->rect.setFillColor(color);
	candy->SetPosition(x * mapTileSize + GetPosition().x + mapTileSize / 2, y * mapTileSize + GetPosition().y + mapTileSize / 2);
	GetScene()->AddGameObject(candy, 0);
	return candy;
}

void Match3::MapUpdater::Start()
{
	input = Engine::GetInstance()->GetModuleManager()->GetModule<InputModule>();
	map = static_cast<MapMatch3*>(owner);
}

void Match3::MapUpdater::Update(TimeModule* timeModule)
{
	HandleInput();
	FillMap();
	if (Gravity()) {
		MatchAll();
	}
}

void Match3::MapUpdater::HandleInput()
{
	if (input->GetMouseButtonPressing(sf::Mouse::Button::Left)) {
		sf::Vector2f mousePos = input->GetMousePosition();
		mousePos.x = (int)(mousePos.x - owner->GetPosition().x) / map->mapTileSize;
		mousePos.y = (int)(mousePos.y - owner->GetPosition().y) / map->mapTileSize;
		if (mousePos.x >= 0 && mousePos.x < map->mapWidth && mousePos.y >= 0 && mousePos.y < map->mapWidth && map->map[mousePos.y * map->mapWidth + mousePos.x]) {
			if (first == sf::Vector2i(-1, -1)) {
				first = static_cast<sf::Vector2i>(mousePos);
			}
			else {
				sf::Vector2i delta = static_cast<sf::Vector2i>(mousePos) - first;
				float distance = sqrt(delta.x * delta.x + delta.y * delta.y);
				if (distance > 1)
					std::cout << "trop loin";
				else
					Swap(first, static_cast<sf::Vector2i>(mousePos));
				first = sf::Vector2i(-1, -1);
			}
		}
	}
}

void Match3::MapUpdater::FillMap()
{
	for (int i = 0; i < map->mapWidth; i++) {
		if (map->map[i] == nullptr) {
			map->map[i] = map->CreateCandy(i % map->mapWidth, 0);
		}
	}
}

bool Match3::MapUpdater::Gravity()
{
	bool res = true;
	for (int i = 0; i < map->mapWidth * (map->mapHeight - 1); i++) {
		if (map->map[i] != nullptr && map->map[i + map->mapWidth] == nullptr) {
			Swap(i, i + map->mapWidth);
			res = false;
		}
	}
	return res;
}

void Match3::MapUpdater::Swap(sf::Vector2i pos1, sf::Vector2i pos2)
{
	Candy* temp = map->map[pos1.y * map->mapWidth + pos1.x];
	map->map[pos1.y * map->mapWidth + pos1.x] = map->map[pos2.y * map->mapWidth + pos2.x];
	map->map[pos2.y * map->mapWidth + pos2.x] = temp;

	if(map->map[pos1.y * map->mapWidth + pos1.x])
		map->map[pos1.y * map->mapWidth + pos1.x]->SetPosition(pos1.x * map->mapTileSize + owner->GetPosition().x + map->mapTileSize / 2, pos1.y * map->mapTileSize + owner->GetPosition().y + map->mapTileSize / 2);
	if(map->map[pos2.y * map->mapWidth + pos2.x])
		map->map[pos2.y * map->mapWidth + pos2.x]->SetPosition(pos2.x * map->mapTileSize + owner->GetPosition().x + map->mapTileSize / 2, pos2.y * map->mapTileSize + owner->GetPosition().y + map->mapTileSize / 2);
}

void Match3::MapUpdater::Swap(int pos1, int pos2)
{
	Candy* temp = map->map[pos1];
	map->map[pos1] = map->map[pos2];
	map->map[pos2] = temp;

	if(map->map[pos1])
		map->map[pos1]->SetPosition(pos1 % map->mapWidth * map->mapTileSize + owner->GetPosition().x + map->mapTileSize / 2, pos1 / map->mapWidth * map->mapTileSize + owner->GetPosition().y + map->mapTileSize / 2);
	if(map->map[pos2])
		map->map[pos2]->SetPosition(pos2 % map->mapWidth * map->mapTileSize + owner->GetPosition().x + map->mapTileSize / 2, pos2 / map->mapWidth * map->mapTileSize + owner->GetPosition().y + map->mapTileSize / 2);
}

void Match3::MapUpdater::MatchAll()
{
	std::vector<Candy*>candyDelete;
	for (int i = 0; i < map->map.size(); i++) {
		if (map->map[i])
			map->map[i]->checked = false;
	}
	for (int i = 0; i < map->map.size();i++) {
		candyDelete.clear();
		if (map->map[i]) {
			CheckCandy(i, map->map[i]->GetId(), candyDelete);
			DeleteCandy(candyDelete);
		}
	}
}

sf::Vector2i Match3::MapUpdater::CheckCandy(int i, int id, std::vector<Candy*>& candyDelete)
{
	sf::Vector2i res;
	if (map->map[i] == nullptr || map->map[i]->GetId() != id || map->map[i]->checked)
		return sf::Vector2i(0, 0);
	map->map[i]->checked = true;
	candyDelete.push_back(map->map[i]);
	if ((i + 1) % map->mapWidth != 0)
		res.x += 1 + CheckCandy(i + 1, id, candyDelete).x;
	else
		res.x++;
	if (i - 1 >= 0 && (i - 1) % map->mapWidth != map->mapWidth - 1)
		res.x += 1 + CheckCandy(i - 1, id, candyDelete).x;
	else
		res.x++;
	if (i + map->mapWidth < map->map.size())
		res.y += 1 + CheckCandy(i + map->mapWidth, id, candyDelete).y;
	else
		res.y++;
	if (i - map->mapWidth >= 0)
		res.y += 1 + CheckCandy(i - map->mapWidth, id, candyDelete).y;
	else
		res.y++;
	return res;
}

void Match3::MapUpdater::DeleteCandy(std::vector<Candy*> deleteCandy)
{
	if (deleteCandy.size() < 3)
		return;
	std::vector<Candy*>form;
	int finish = 0;
	for (int i = 0; i < deleteCandy.size();i++) {
		if (form.size() < 2)
			form.push_back(deleteCandy[i]);
		else if (form[form.size() - 1]->GetPosition().x == form[form.size() - 2]->GetPosition().x) {
			if (deleteCandy[i]->GetPosition().x == form[form.size() -1]->GetPosition().x) {
				form.push_back(deleteCandy[i]);
			}
			else 
			{
				finish = i;
				break;
			}
		}
		else if (form[form.size() -1]->GetPosition().y == form[form.size() -2]->GetPosition().y) {
			if (deleteCandy[i]->GetPosition().y == form[form.size() -1]->GetPosition().y) {
				form.push_back(deleteCandy[i]);
			}
			else
			{
				finish = i;
				break;
			}
		}
	}
	for (int i = finish; i < deleteCandy.size(); i++) {
		deleteCandy[i]->checked = false;
	}
	if(form.size() >= 3)
	{
		for (Candy* candy : form) {
			for (Candy*& mapCandy : map->map) {
				if (mapCandy == candy)
					mapCandy = nullptr;
			}
			owner->GetScene()->DestroyObject(candy);
		}
	}
	else {
		for (Candy* candy : form) {
			candy->checked = false;
		}
	}
}

void Match3::MapUpdater::PrintCandyDelete(std::vector<Candy*> candies)
{
	for (Candy* candy : candies) {
		std::cout << (int)(candy->GetPosition().x - owner->GetPosition().x) / map->mapTileSize << " : " << (int)(candy->GetPosition().y - owner->GetPosition().y) / map->mapTileSize << ", ";
	}
}

void Match3::MapRender::Start()
{
	map = static_cast<MapMatch3*>(owner);
	border.setFillColor(sf::Color::Transparent);
	border.setOutlineColor(sf::Color::White);
	border.setSize({ (float)map->mapTileSize, (float)map->mapTileSize });
	border.setOutlineThickness(1);
}

void Match3::MapRender::Render(WindowModule* window)
{
	for (int y = 0; y < map->mapHeight; y++) {
		for (int x = 0; x < map->mapWidth; x++) {
			border.setPosition({ x * map->mapTileSize + owner->GetPosition().x, y * map->mapTileSize + owner->GetPosition().y });
			window->GetWindow()->draw(border);
		}
	}
}
