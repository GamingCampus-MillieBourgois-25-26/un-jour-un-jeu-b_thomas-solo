#include <Include/Match3/Match3.h>
#include <Include/Match3/MapMatch3.h>

Match3::Match3::Match3()
{
	MapMatch3* map = new MapMatch3();
	map->SetPosition(100,100);
	AddGameObject(map, 1);

}
