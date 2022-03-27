#include "csquare.h"

int CSquare::Id() const
{
    return fId;
}

std::string CSquare::DisplayName() const
{
    return fDisplayName;
}

CSquare::CSquare(int id, bool isEmpty, std::string displayName)
    : fId(id), fDisplayName(displayName), fIsEmpty(isEmpty)
{

}
