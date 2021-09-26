#include "stdafx.h"
#include "player.h"

HRESULT player::init()
{
	addItem(HPPotion, 5);
	addItem(SPPotion, 5);

	_gold = 10000;

	return S_OK;
}

void player::addItem(ITMEINFO iteminfo)
{
	INVENTORY inven;
	ITEM item;

	switch (iteminfo)
	{
		case HPPotion:
		{
			item.iconNum = 0;
			item.name = "체력회복약";
			item.info = iteminfo;
			item.price = 100;
		}
		break;

		case SPPotion:
		{
			item.iconNum = 1;
			item.name = "기력환단";
			item.info = iteminfo;
			item.price = 200;
		}
		break;
	}

	for (int i = 0; i < _inventory.size(); i++)
	{
		if (_inventory[i].item.info == item.info)
		{
			_inventory[i].count++;
			return;
		}
	}

	inven.item = item;
	inven.count = 1;
	_inventory.push_back(inven);
	return;
}

void player::addItem(ITMEINFO iteminfo, int count)
{
	INVENTORY inven;
	ITEM item;

	switch (iteminfo)
	{
	case HPPotion:
	{
		item.iconNum = 0;
		item.name = "체력회복약";
		item.info = iteminfo;
		item.price = 100;
	}
	break;

	case SPPotion:
	{
		item.iconNum = 1;
		item.name = "기력환단";
		item.info = iteminfo;
		item.price = 200;
	}
	break;
	}

	for (int i = 0; i < _inventory.size(); i++)
	{
		if (_inventory[i].item.info == item.info)
		{
			_inventory[i].count += count;
			return;
		}
	}

	inven.item = item;
	inven.count = count;
	_inventory.push_back(inven);
	return;
}

void player::subItem(ITMEINFO iteminfo)
{
	INVENTORY inven;
	ITEM item;

	switch (iteminfo)
	{
	case HPPotion:
	{
		item.iconNum = 0;
		item.name = "체력회복약";
		item.info = iteminfo;
		item.price = 100;
	}
	break;

	case SPPotion:
	{
		item.iconNum = 1;
		item.name = "기력환단";
		item.info = iteminfo;
		item.price = 200;
	}
	break;
	}

	for (int i = 0; i < _inventory.size(); i++)
	{
		if (_inventory[i].item.info == item.info)
		{
			_inventory[i].count--;

			if (_inventory[i].count <= 0)
			{
				_inventory.erase(_inventory.begin() + i);
			}
			return;
		}
	}
}

void player::subItem(ITMEINFO iteminfo, int count)
{
	INVENTORY inven;
	ITEM item;

	switch (iteminfo)
	{
	case HPPotion:
	{
		item.iconNum = 0;
		item.name = "체력회복약";
		item.info = iteminfo;
		item.price = 100;
	}
	break;

	case SPPotion:
	{
		item.iconNum = 1;
		item.name = "기력환단";
		item.info = iteminfo;
		item.price = 200;
	}
	break;
	}

	for (int i = 0; i < _inventory.size(); i++)
	{
		if (_inventory[i].item.info == item.info)
		{
			_inventory[i].count -= count;

			if (_inventory[i].count <= 0)
			{
				_inventory.erase(_inventory.begin() + i);
			}
			return;
		}
	}
}
