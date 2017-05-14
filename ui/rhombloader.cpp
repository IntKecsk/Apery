#include "dimensions.h"
#include "rhombloader.h"

#include <QBitmap>

template struct RhombTraits<QRect>;
template struct RhombTraits<QBitmap>;
template struct RhombTraits<QPixmap>;

namespace
{

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
RectCoeffs srcWideProto[10] = {

    //source           size
    //o  i  d  o  i    o  i  d  o  i
    {{2, 0, 1, 1, 0}, {0, 2, 0, 0, 2}},
    {{0, 2, 0, 0, 1}, {1, 0, 1, 1, 0}},
    {{1, 0, 1, 0, 0}, {1, 1, 0, 1, 1}},
    {{0, 1, 0, 0, 0}, {1, 1, 0, 1, 1}},
    {{1, 0, 0, 0, 1}, {1, 0, 1, 1, 0}},
    {{0, 0, 0, 1, 0}, {0, 2, 0, 0, 2}},
    {{1, 0, 0, 1, 1}, {1, 0, 1, 1, 0}},
    {{0, 1, 0, 1, 1}, {1, 1, 0, 1, 1}},
    {{1, 0, 1, 1, 1}, {1, 1, 0, 1, 1}},
    {{0, 2, 0, 1, 1}, {1, 0, 1, 1, 0}}
};

RectCoeffs srcNarrowProto[10] = {
    //source           size
    //o  i  d  o  i    o  i  d  o  i
    {{0, 0, 0, 0, 1}, {2, 0, 0, 2, 0}},
    {{0, 0, 0, 1, 1}, {1, 1, 0, 1, 1}},
    {{1, 0, 0, 2, 1}, {0, 1, 1, 0, 1}},
    {{1, 1, 0, 2, 1}, {0, 1, 1, 0, 1}},
    {{1, 1, 1, 1, 1}, {1, 1, 0, 1, 1}},
    {{0, 2, 1, 0, 1}, {2, 0, 0, 2, 0}},
    {{1, 1, 1, 0, 0}, {1, 1, 0, 1, 1}},
    {{1, 1, 0, 0, 0}, {0, 1, 1, 0, 1}},
    {{1, 0, 0, 0, 0}, {0, 1, 1, 0, 1}},
    {{0, 0, 0, 0, 0}, {1, 1, 0, 1, 1}}
};
}

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

    for (int i=0; i<10; i++)
    {
        m_wsrc[i] = m_vec.rect(srcWideProto[i]);
        m_nsrc[i] = m_vec.rect(srcNarrowProto[i]);
    }
    m_ssz = m_vec.size({2,2,1,2,2});
}

bool RhombLoader::load(const QPixmap& src)
{
    if(src.width()<m_ssz.width() || src.height()<m_ssz.height())
        return false;

    auto bmp = std::static_pointer_cast<RhombBmpSimple>(m_bmp);
    QPixmap cs[2];
    cs[0]=src.copy(QRect(QPoint(0,0), m_ssz));
    if(src.width()>=2*m_ssz.width())
        cs[1] = src.copy(QRect(QPoint(m_ssz.width(),0), m_ssz));
    else
        cs[1] = cs[0].transformed(QTransform(-1, 0, 0, -1, 0, 0));
    auto pix = std::make_shared<RhombPixSimple>();
    for(int i=0;i<10;i++)
    {
        pix->m_wide[i]=cs[i%2].copy(m_wsrc[i]);
        pix->m_wide[i].setMask(bmp->m_wide[i%5]);
        pix->m_narrow[i]=cs[i%2].copy(m_nsrc[i]);
        pix->m_narrow[i].setMask(bmp->m_narrow[i%5]);
    }
    emit loaded(m_vec, m_dim, m_bmp, pix);
    return true;
}
