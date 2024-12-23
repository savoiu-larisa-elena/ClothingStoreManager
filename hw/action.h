#pragma once
#include "repository.h"

class Action
{
public:
    virtual void execute_undo() = 0;
    virtual void execute_redo() = 0;
    virtual ~Action() = default;
};

class AddAction : public Action
{
private:
    Coat coat;
    Repository* repository;
public:
    AddAction(Coat coat, Repository* repository) : coat{ coat }, repository{ repository } {};
    void execute_undo() override;
    void execute_redo() override;
};

class DeleteAction : public Action
{
private:
    Coat coat;
    Repository* repository;
public:
    DeleteAction(Coat coat, Repository* repository) : coat{ coat }, repository{ repository } {};
    void execute_undo() override;
    void execute_redo() override;
};

class UpdateAction : public Action
{
private:
    Coat coat;
    Coat new_coat;
    Repository* repository;
public:
    UpdateAction(Coat coat, Coat new_coat, Repository* repository) : coat{ coat }, new_coat{ new_coat }, repository{ repository } {};
    void execute_undo() override;
    void execute_redo() override;
};

class AddToShoppingBasketAction : public Action
{
private:
    Coat coat;
    Repository* repository;
public:
    AddToShoppingBasketAction(Coat coat, Repository* repository) : coat{ coat }, repository{ repository } {};
    void execute_undo() override;
    void execute_redo() override;
};