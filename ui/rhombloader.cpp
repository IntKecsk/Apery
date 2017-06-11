#include "dimensions.h"
#include "rhombloader.h"

#include <QBitmap>
#include <QPainter>

namespace
{

template<typename TOfs>
struct RhombSource
{
    TOfs ofs;
    int plane;
};

template<typename T>
struct Simple
{
    const T& get(Tile t) const;
    template<typename Fn, typename... Y>
    void transform(Fn func, Simple<Y>&... out) const;

    T w[10];
    T n[10];
};


template<typename T>
const T& Simple<T>::get(Tile t) const
{
    if (t.nmn > 3)
        return n[t.ori];
    else
        return w[t.ori];
}

template<typename T>
template<typename Fn, typename... Y>
void Simple<T>::transform(Fn func, Simple<Y>&... out) const
{
    for (uint8 i = 0; i < 10; i++)
        func({i, 0}, w[i], out.w[i]...);

    for (uint8 i = 0; i < 10; i++)
        func({i, 4}, n[i], out.n[i]...);
}


template<typename T>
struct Neumann
{
    const T& get(Tile t) const;
    template<typename Fn, typename... Y>
    void transform(Fn func, Neumann<Y>&... out) const;

    T d[7][10];
};

template<typename T>
const T& Neumann<T>::get(Tile t) const
{
    return d[t.nmn][t.ori];
}

template<typename T>
template<typename Fn, typename... Y>
void Neumann<T>::transform(Fn func, Neumann<Y>&... out) const
{
    for (uint8 i = 0; i < 7; i++)
    {
        for (uint8 j = 0; j < 10; j++)
            func({j, i}, d[i][j], out.d[i][j]...);
    }
}

template<typename TOfs>
using SimpleSources = Simple<RhombSource<TOfs>>;

template<typename TOfs>
using NeumannSources = Neumann<RhombSource<TOfs>>;

RectCoeffs dimWideProto[10] = {
    //offset                size
    // o   i   d   o   i    o  i  d  o  i
    {{ 0,  0,  0,  0, -1}, {0, 2, 0, 0, 2}},
    {{ 0,  0,  0, -1,  0}, {1, 0, 1, 1, 0}},
    {{-1,  0,  0, -1, -1}, {1, 1, 0, 1, 1}},
    {{ 0, -1,  0, -1, -1}, {1, 1, 0, 1, 1}},
    {{-1,  0, -1, -1,  0}, {1, 0, 1, 1, 0}},
    {{ 0, -2,  0,  0, -1}, {0, 2, 0, 0, 2}},
    {{-1,  0, -1,  0,  0}, {1, 0, 1, 1, 0}},
    {{ 0, -1,  0,  0,  0}, {1, 1, 0, 1, 1}},
    {{-1,  0,  0,  0,  0}, {1, 1, 0, 1, 1}},
    {{ 0,  0,  0,  0,  0}, {1, 0, 1, 1, 0}}
};

RectCoeffs dimNarrowProto[10] = {
    //offset                size
    // o   i   d   o   i    o  i  d  o  i
    {{ 0,  0,  0, -1,  0}, {2, 0, 0, 2, 0}},
    {{-1,  0,  0, -1,  0}, {1, 1, 0, 1, 1}},
    {{ 0, -1,  0,  0, -1}, {0, 1, 1, 0, 1}},
    {{ 0,  0, -1,  0, -1}, {0, 1, 1, 0, 1}},
    {{ 0, -1,  0, -1,  0}, {1, 1, 0, 1, 1}},
    {{-2,  0,  0, -1,  0}, {2, 0, 0, 2, 0}},
    {{ 0, -1,  0,  0, -1}, {1, 1, 0, 1, 1}},
    {{ 0,  0, -1,  0,  0}, {0, 1, 1, 0, 1}},
    {{ 0, -1,  0,  0,  0}, {0, 1, 1, 0, 1}},
    {{-1,  0,  0,  0, -1}, {1, 1, 0, 1, 1}}
};

SimpleSources<Coeffs> srcSimpleProto = {
    //wide
    {
        //offset          plane
        //o  i  d  o  i
        {{2, 0, 1, 1, 0}, 0},
        {{0, 2, 0, 0, 1}, 1},
        {{1, 0, 1, 0, 0}, 0},
        {{0, 1, 0, 0, 0}, 1},
        {{1, 0, 0, 0, 1}, 0},
        {{0, 0, 0, 1, 0}, 1},
        {{1, 0, 0, 1, 1}, 0},
        {{0, 1, 0, 1, 1}, 1},
        {{1, 0, 1, 1, 1}, 0},
        {{0, 2, 0, 1, 1}, 1}
    },
    //narrow
    {
        //offset          plane
        //o  i  d  o  i
        {{0, 0, 0, 0, 1}, 0},
        {{0, 0, 0, 1, 1}, 1},
        {{1, 0, 0, 2, 1}, 0},
        {{1, 1, 0, 2, 1}, 1},
        {{1, 1, 1, 1, 1}, 0},
        {{0, 2, 1, 0, 1}, 1},
        {{1, 1, 1, 0, 0}, 0},
        {{1, 1, 0, 0, 0}, 1},
        {{1, 0, 0, 0, 0}, 0},
        {{0, 0, 0, 0, 0}, 1}
    }
};

NeumannSources<Coeffs> srcNeumannProto = {
    {
        //M
        {
            //offset          plane
            //o  i  d  o  i
            {{2, 0, 0, 2, 1}, 0},
            {{0, 1, 0, 2, 3}, 1},
            {{1, 1, 1, 3, 2}, 0},
            {{1, 2, 1, 3, 2}, 1},
            {{2, 3, 1, 2, 3}, 0},
            {{1, 2, 2, 2, 1}, 1},
            {{2, 3, 1, 1, 1}, 0},
            {{1, 2, 1, 0, 1}, 1},
            {{1, 1, 1, 0, 1}, 0},
            {{0, 1, 0, 1, 1}, 1}
        },
        //KL
        {
            //offset          plane
            //o  i  d  o  i
            {{2, 1, 1, 0, 0}, 0},
            {{0, 1, 0, 0, 1}, 1},
            {{1, 0, 0, 1, 1}, 0},
            {{0, 0, 0, 2, 2}, 1},
            {{1, 1, 0, 3, 3}, 0},
            {{1, 1, 1, 4, 2}, 1},
            {{2, 3, 1, 3, 3}, 0},
            {{1, 3, 2, 2, 2}, 1},
            {{2, 3, 2, 1, 1}, 0},
            {{1, 3, 1, 0, 1}, 1}
        },
        //KJ
        {
            //offset          plane
            //o  i  d  o  i
            {{2, 1, 1, 4, 2}, 0},
            {{1, 3, 1, 3, 3}, 1},
            {{2, 3, 2, 2, 2}, 0},
            {{1, 3, 2, 1, 1}, 1},
            {{2, 3, 1, 0, 1}, 0},
            {{1, 1, 1, 0, 0}, 1},
            {{1, 1, 0, 0, 1}, 0},
            {{0, 0, 0, 1, 1}, 1},
            {{1, 0, 0, 2, 2}, 0},
            {{0, 1, 0, 3, 3}, 1}
        },
        //Q
        {
            //offset          plane
            //o  i  d  o  i
            {{1, 0, 1, 2, 1}, 1},
            {{1, 2, 0, 2, 2}, 0},
            {{1, 1, 1, 2, 2}, 1},
            {{1, 2, 1, 2, 2}, 0},
            {{1, 2, 1, 2, 2}, 1},
            {{2, 2, 1, 2, 1}, 0},
            {{1, 2, 1, 1, 2}, 1},
            {{1, 2, 1, 1, 1}, 0},
            {{1, 1, 1, 1, 1}, 1},
            {{1, 2, 0, 1, 2}, 0}
        },
        //k
        {
            //offset          plane
            //o  i  d  o  i
            {{1, 4, 2, 1, 2}, 1},
            {{2, 3, 2, 0, 1}, 0},
            {{1, 2, 1, 0, 0}, 1},
            {{2, 1, 0, 0, 0}, 0},
            {{0, 0, 0, 0, 1}, 1},
            {{0, 0, 0, 1, 2}, 0},
            {{0, 0, 0, 3, 2}, 1},
            {{2, 1, 0, 4, 3}, 0},
            {{1, 2, 1, 4, 3}, 1},
            {{2, 3, 2, 3, 2}, 0}
        },
        //qq
        {
            //offset          plane
            //o  i  d  o  i
            {{1, 3, 1, 0, 1}, 0},
            {{1, 1, 1, 0, 1}, 1},
            {{1, 1, 0, 1, 1}, 0},
            {{1, 0, 0, 2, 1}, 1},
            {{1, 1, 0, 2, 2}, 0},
            {{0, 1, 1, 2, 3}, 1},
            {{1, 2, 1, 3, 2}, 0},
            {{2, 2, 1, 3, 2}, 1},
            {{2, 3, 1, 2, 2}, 0},
            {{1, 2, 2, 1, 1}, 1}
        },
        //qp
        {
            //offset          plane
            //o  i  d  o  i
            {{1, 3, 1, 2, 3}, 0},
            {{1, 2, 2, 2, 2}, 1},
            {{2, 3, 1, 2, 1}, 0},
            {{2, 2, 1, 1, 1}, 1},
            {{1, 2, 1, 0, 1}, 0},
            {{0, 1, 1, 0, 1}, 1},
            {{1, 1, 0, 1, 1}, 0},
            {{1, 0, 0, 2, 2}, 1},
            {{1, 1, 0, 3, 2}, 0},
            {{1, 1, 1, 3, 2}, 1}
        }
    }
};

struct SourceSize
{
    QSize ext;
    QSize ssz;
    bool dup; ///< separate images for 180 degree rotation
    bool nmn; ///< von Neumann (S5) or simple (S) source
};
}

struct RhombSources
{
    template<template<typename> class TData>
    const TData<RhombSource<QPoint>>& get();

    SimpleSources<QPoint> m_simple;
    NeumannSources<QPoint> m_neumann;
};

template<>
const SimpleSources<QPoint>& RhombSources::get<Simple>()
{
    return m_simple;
}

template<>
const NeumannSources<QPoint>& RhombSources::get<Neumann>()
{
    return m_neumann;
}

RhombDim::RhombDim(const Vectors& vec)
{
    for (int i=0; i<10; i++)
    {
        m_wide[i] = vec.rect(dimWideProto[i]);
        m_narrow[i] = vec.rect(dimNarrowProto[i]);
    }
}

const QRect& RhombDim::get(Tile t) const
{
    if (t.nmn > 3)
        return m_narrow[t.ori];
    else
        return m_wide[t.ori];
}

template<typename TImg>
const TImg& RhombMask<TImg>::get(Tile t) const
{
    if (t.nmn > 3)
        return m_narrow[t.ori % 5];
    else
        return m_wide[t.ori % 5];
}

template struct RhombMask<QImage>;
template struct RhombMask<QBitmap>;

template<template<typename> class TData>
struct RhombPixImpl : RhombPix
{
    virtual const QPixmap& get(int state, Tile t) const override;
    virtual int nstates() const override;

    QVector<TData<QPixmap>> m_pix;
};

template<template<typename> class TData>
const QPixmap& RhombPixImpl<TData>::get(int state, Tile t) const
{
    return m_pix.at(state).get(t);
}

template<template<typename> class TData>
int RhombPixImpl<TData>::nstates() const
{
    return m_pix.size();
}

struct RhombLoader::Impl
{
    RhombSources src;
    QList<SourceSize> ssz;
    RhombMask<QBitmap> bmp;
};

RhombLoader::RhombLoader(QObject *parent) : QObject(parent),
    m_vec{QPoint(7, 23), QPoint(19, 14), 24}
{
    m_i.reset(new Impl);
    m_dim = std::make_shared<RhombDim>(m_vec);
    m_mask = std::make_shared<RhombMask<QImage>>();

    QString fn = ":/f%1.png", sn = ":/s%1.png";

    for(int i=0;i<5;i++)
    {
        m_mask->m_wide[i].load(fn.arg(i));
        m_i->bmp.m_wide[i] = QBitmap::fromImage(m_mask->m_wide[i]);
        m_mask->m_narrow[i].load(sn.arg(i));
        m_i->bmp.m_narrow[i] = QBitmap::fromImage(m_mask->m_narrow[i]);
    }

    QSize simple = m_vec.size({2,2,1,2,2});
    QSize neumann = m_vec.size({3,4,2,4,4});

    m_i->ssz.append({QSize(neumann.width()*2, neumann.height()), neumann, true, true});
    m_i->ssz.append({QSize(simple.width()*2, simple.height()), simple, true, false});
    m_i->ssz.append({neumann, neumann, false, true});
    m_i->ssz.append({simple, simple, false, false});

    auto concr = [&vec = m_vec](Tile, const RhombSource<Coeffs>& in, RhombSource<QPoint>& out)
    {
        out = {vec.point(in.ofs), in.plane};
    };

    srcSimpleProto.transform(concr, m_i->src.m_simple);
    srcNeumannProto.transform(concr, m_i->src.m_neumann);
}

RhombLoader::~RhombLoader() = default;

bool RhombLoader::load(const QPixmap& src, int nstates)
{
    QSize ssz;
    bool dup = false, nmn = false;

    for(const SourceSize& s: m_i->ssz)
    {
        if (src.width() >= s.ext.width() && src.height() >= s.ext.height())
        {
            ssz = s.ssz;
            dup = s.dup;
            nmn = s.nmn;
            break;
        }
    }

    if(ssz.isEmpty() || src.height() / ssz.height() < nstates)
        return false;

    if (nmn)
        return doLoad<Neumann>(src, ssz, nstates, dup);
    else
        return doLoad<Simple>(src, ssz, nstates, dup);
}

QImage RhombLoader::dump(bool nmn)
{
    if (nmn)
        return doDump<Neumann>(m_i->ssz.at(0).ssz);
    else
        return doDump<Simple>(m_i->ssz.at(1).ssz);
}

template<template<typename> class TData>
bool RhombLoader::doLoad(const QPixmap& src, const QSize& ssz, int nstates, bool dup)
{
    auto pix = std::make_shared<RhombPixImpl<TData>>();
    pix->m_pix.resize(nstates);

    for (int i = 0; i < nstates; i++)
    {
        QPixmap cs[2];
        cs[0]=src.copy(QRect(QPoint(0, i * ssz.height()), ssz));
        if(dup)
            cs[1] = src.copy(QRect(QPoint(ssz.width(), i * ssz.height()), ssz));
        else
            cs[1] = cs[0].transformed(QTransform(-1, 0, 0, -1, 0, 0));

        m_i->src.get<TData>().transform(
            [&cs, &dim=m_dim, &bmp=m_i->bmp](Tile t, const RhombSource<QPoint>& in, QPixmap& out)
        {
            out = cs[in.plane].copy(QRect(in.ofs, dim->get(t).size()));
            out.setMask(bmp.get(t));
            return;
        }, pix->m_pix[i]);
    }

    m_pix = pix;
    emit loaded(m_vec, m_dim, m_mask, pix);
    return true;
}

template<template<typename> class TData>
QImage RhombLoader::doDump(const QSize& ssz)
{
    int nstates = m_pix->nstates();
    int w = ssz.width(), h = ssz.height();
    QImage res(QSize(2 * w, nstates * h), QImage::Format_ARGB32);
    res.fill(Qt::white);

    QPainter pp(&res);

    QPoint pofs[2]{{0, 0}, {w, 0}};
    QPoint sofs(0, h);

    for(int i = 0; i < nstates; i++)
    {
        m_i->src.get<TData>().transform([&, &pix=m_pix](Tile t, const RhombSource<QPoint>& in)
        {
            pp.drawPixmap(in.ofs + pofs[in.plane] + sofs * i, pix->get(i, t));
        });
    }

    return res;
}
