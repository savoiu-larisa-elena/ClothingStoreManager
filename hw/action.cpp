#include "../hw/action.h"

void AddAction::execute_undo()
{
	this->repository->delete_coat(this->coat);
}

void AddAction::execute_redo()
{
	this->repository->add_coat(this->coat);
}

void DeleteAction::execute_undo()
{
	this->repository->add_coat(this->coat);
}

void DeleteAction::execute_redo()
{
	this->repository->delete_coat(this->coat);
}

void UpdateAction::execute_undo()
{
	this->repository->update_coat(this->new_coat, this->coat);
}

void UpdateAction::execute_redo()
{
	this->repository->update_coat(this->coat, this->new_coat);
}

void AddToShoppingBasketAction::execute_undo()
{
	this->repository->delete_coat(this->coat);
}

void AddToShoppingBasketAction::execute_redo()
{
	this->repository->add_coat(this->coat);
}