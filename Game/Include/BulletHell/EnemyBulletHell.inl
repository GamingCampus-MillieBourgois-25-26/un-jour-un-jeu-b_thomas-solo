#pragma once
template<typename Patern, typename... Param>
inline void BulletHell::PaternManager::CreatePatern(Param... parameters)
{
	Patern* newPatern = new Patern(parameters...);
	paterns.push_back(newPatern);
}