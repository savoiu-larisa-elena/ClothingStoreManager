#pragma once
#include <iostream>
#include <string>
#include <vector>
#include "services.h"
#include "repository.h"
#include "domain.h"


class ActiuneUndo {
public:
    virtual void doUndo() = 0;
    //destructor virtual
    virtual ~ActiuneUndo() = default;

};

//clasa pentru undo adauga care mosteneste metotdele lui actiuneundo
class UndoAdauga :public ActiuneUndo {
    Coat coat_added;
    Repository& repo;
public:
    UndoAdauga(const Coat& coat, Repository& repo) : repo{ repo }, coat_added(coat) {};
    void doUndo() override {
        repo.delete_coat(coat_added);
    }
};

//undo delete

class UndoSterge :public ActiuneUndo {
    Coat to_readd;
    Repository& repo;
public:
    UndoSterge(Repository& repo, const Coat& coat) : repo{ repo }, to_readd{ coat } {};
    void doUndo() override {
        repo.add_coat(to_readd);
    }
};

class UndoModifica :public ActiuneUndo {
    Coat coat_Added;
    Repository& repo;
public:
    UndoModifica(const Coat& coat, Repository& repo) : repo{ repo }, coat_Added(coat) {};
    void doUndo() override {
        repo.update_coat(coat_Added, coat_Added);
    }
};