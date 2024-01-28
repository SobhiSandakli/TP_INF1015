#include "caisse.h"
#include "exception.h"

Caisse::~Caisse()
{
    while (!articles_.empty()) {
        delete articles_.back();
        articles_.pop_back();
    }
}

void Caisse:: ajouterArticle(Article* article)
{
    if (article->description!="" && article->prix!=0)
    {
        articles_.push_back(article);
        totalAvantTaxes_ += article->prix;
        emit refresh();
    }
    else{
        if (article->description=="") {throw ExceptionDescriptionVide("La description de l'article est vide");}
        else {throw ExceptionPrixNul("Le prix de l'article est nul");}
    }
}

void Caisse:: retirerArticle(Article* article)
{
    auto it = find(articles_.begin(), articles_.end(), article);

    if(it!=articles_.end()){
        articles_.erase(it);
        totalAvantTaxes_ -= article->prix;
        emit refresh();
    }
}

vector<Article*> Caisse::getListeArticle() const
{
    return articles_;
}

double Caisse::getTotalTaxes() const
{
    return std::transform_reduce(articles_.cbegin(), articles_.cend(), 0.0, std::plus<double>(),
                                 [](Article* a){return a->taxable? a->prix * 0.14975: 0.0;});
}
