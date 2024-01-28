#ifndef CAISSE_H
#define CAISSE_H
#include <QMainWindow>
#include <QBoxLayout>
#include <vector>
using namespace std;

struct Article{
    string description;
    double prix;
    bool taxable;

    bool operator==(const Article& a) const
    {
        if ((description == a.description) && (prix == a.prix) && (taxable == a.taxable)) {return true;}
        return false;
    }
};

class Caisse: public QObject
{
    Q_OBJECT
public:
    Caisse() = default;
    ~Caisse();
    void ajouterArticle(Article* article);
    void retirerArticle(Article* article);
    vector<Article*> getListeArticle() const;
    double getTotalPreTaxes() const {return totalAvantTaxes_;};
    double getTotalTaxes() const ;

private:
    vector<Article*> articles_;
    double totalAvantTaxes_;

signals:
    void refresh();
};


#endif // CAISSE_H
