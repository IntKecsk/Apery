#include "dimensions.h"
#include "rhombloader.h"

#include <QBitmap>

template struct RhombTraits<QRect>;
template struct RhombTraits<QBitmap>;
template struct RhombTraits<QPixmap>;

namespace
{

template<typename TOfs>
struct RhombSource
{
    TOfs ofs;
    int plane;
};

RhombSource<QPoint> rsFromProto(const RhombSource<Coeffs>& proto, const Vectors& vec)
{
    return {vec.point(proto.ofs), proto.plane};
}

template<typename TOfs>
struct SimpleSources
{
    RhombSource<TOfs> wide[10];
    RhombSource<TOfs> narrow[10];
};

template<typename TOfs>
struct NeumannSources
{
    RhombSource<TOfs> src[7][10];
};

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
    SimpleSources<QPoint> m_simple;
    NeumannSources<QPoint> m_neumann;
};

struct SourceSizes
{
    QList<SourceSize> list;
};

struct RhombDimSimple : RhombTraits<QRect>
{
    explicit RhombDimSimple(const Vectors& oid);

    virtual QRect get(uint8 ori, uint8 nmn) const override;
    QRect m_wide[10];
    QRect m_narrow[10];
};

struct RhombBmpSimple : RhombTraits<QBitmap>
{
    virtual QBitmap get(uint8 ori, uint8 nmn) const override;
    QBitmap m_wide[5];
    QBitmap m_narrow[5];
};

struct RhombPixSimple : RhombTraits<QPixmap>
{
    virtual QPixmap get(uint8 ori, uint8 nmn) const override;
    QPixmap m_wide[10];
    QPixmap m_narrow[10];
};

struct RhombPixNeumann : RhombTraits<QPixmap>
{
    virtual QPixmap get(uint8 ori, uint8 nmn) const override;
    QPixmap m_pix[7][10];
};

RhombDimSimple::RhombDimSimple(const Vectors& oid)
{
    for (int i=0; i<10; i++)
    {
        m_wide[i] = oid.rect(dimWideProto[i]);
        m_narrow[i] = oid.rect(dimNarrowProto[i]);
    }
}

QRect RhombDimSimple::get(uint8 ori, uint8 nmn) const
{
    if (nmn > 3)
        return m_narrow[ori];
    else
        return m_wide[ori];
}

QBitmap RhombBmpSimple::get(uint8 ori, uint8 nmn) const
{
    if (nmn > 3)
        return m_narrow[ori % 5];
    else
        return m_wide[ori % 5];
}

QPixmap RhombPixSimple::get(uint8 ori, uint8 nmn) const
{
    if (nmn > 3)
        return m_narrow[ori];
    else
        return m_wide[ori];
}

QPixmap RhombPixNeumann::get(uint8 ori, uint8 nmn) const
{
    return m_pix[nmn][ori];
}

RhombLoader::RhombLoader(QObject *parent) : QObject(parent),
    m_vec{QPoint(7, 23), QPoint(19, 14), 24}
{
    m_dim = std::make_shared<RhombDimSimple>(m_vec);

    auto bmp = std::make_shared<RhombBmpSimple>();
    QString fn = ":/f%1.png", sn = ":/s%1.png";

    for(int i=0;i<5;i++)
    {
        bmp->m_wide[i].load(fn.arg(i));
        bmp->m_narrow[i].load(sn.arg(i));
    }
    m_bmp = std::move(bmp);

    QSize simple = m_vec.size({2,2,1,2,2});
    QSize neumann = m_vec.size({3,4,2,4,4});

    m_ssz.reset(new SourceSizes);

    m_ssz->list.append({QSize(neumann.width()*2, neumann.height()), neumann, true, true});
    m_ssz->list.append({QSize(simple.width()*2, simple.height()), simple, true, false});
    m_ssz->list.append({neumann, neumann, false, true});
    m_ssz->list.append({simple, simple, false, false});

    m_src.reset(new RhombSources);
    for (int i=0; i<10; i++)
    {
        m_src->m_simple.wide[i] = rsFromProto(srcSimpleProto.wide[i], m_vec);
        m_src->m_simple.narrow[i] = rsFromProto(srcSimpleProto.narrow[i], m_vec);
    }

    for (int i=0; i<7; i++)
    {
        for (int j=0; j<10; j++)
            m_src->m_neumann.src[i][j] = rsFromProto(srcNeumannProto.src[i][j], m_vec);
    }
}

RhombLoader::~RhombLoader() = default;

bool RhombLoader::load(const QPixmap& src)
{
    QSize ssz;
    bool dup = false, nmn = false;

    for(const SourceSize& s: m_ssz->list)
    {
        if (src.width() >= s.ext.width() && src.height() >= s.ext.height())
        {
            ssz = s.ssz;
            dup = s.dup;
            nmn = s.nmn;
            break;
        }
    }

    if(ssz.isEmpty())
        return false;

    auto bmp = std::static_pointer_cast<RhombBmpSimple>(m_bmp);
    auto dim = std::static_pointer_cast<RhombDimSimple>(m_dim);
    QPixmap cs[2];
    cs[0]=src.copy(QRect(QPoint(0,0), ssz));
    if(dup)
        cs[1] = src.copy(QRect(QPoint(ssz.width(),0), ssz));
    else
        cs[1] = cs[0].transformed(QTransform(-1, 0, 0, -1, 0, 0));

    if (nmn)
    {
        auto pix = std::make_shared<RhombPixNeumann>();
        for (int i = 0; i < 7; i++)
        {
            const auto& r = i > 3 ? dim->m_narrow : dim->m_wide;
            const auto& m = i > 3 ? bmp->m_narrow : bmp->m_wide;
            for (int j = 0; j < 10; j++)
            {
                const auto& s = m_src->m_neumann.src;
                pix->m_pix[i][j] = cs[s[i][j].plane].copy(QRect(s[i][j].ofs, r[j].size()));
                pix->m_pix[i][j].setMask(m[j%5]);
            }
        }
        emit loaded(m_vec, m_dim, m_bmp, pix);
    }
    else
    {
        auto pix = std::make_shared<RhombPixSimple>();
        for(int i = 0; i < 10; i++)
        {
            const auto& w = m_src->m_simple.wide;
            const auto& n = m_src->m_simple.narrow;
            pix->m_wide[i]=cs[w[i].plane].copy(QRect(w[i].ofs, dim->m_wide[i].size()));
            pix->m_wide[i].setMask(bmp->m_wide[i%5]);
            pix->m_narrow[i]=cs[n[i].plane].copy(QRect(n[i].ofs, dim->m_narrow[i].size()));
            pix->m_narrow[i].setMask(bmp->m_narrow[i%5]);
        }
        emit loaded(m_vec, m_dim, m_bmp, pix);
    }
    return true;
}
