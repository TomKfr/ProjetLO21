#include "completion.h"
#include "cursus.h"

void souhaits::Ajt_exigence(const QString& code)
{
    exigences.insert(code);
}
void souhaits::Ajt_preference(const QString& code)
{
    preferences.insert(code);
}
void souhaits::Ajt_rejet(const QString& code)
{
    rejets.insert(code);
}
void souhaits::Suppr_exigence(const QString& code)
{
    exigences.remove(code);
}
void souhaits::Suppr_prefernce(const QString& code)
{
    preferences.remove(code);
}
void souhaits::Suppr_rejet(const QString& code)
{
    rejets.remove(code);
}
