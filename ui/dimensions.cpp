#include "dimensions.h"

QPoint Vectors::point(const Coeffs& mp) const
{
    return QPoint(o.x()*mp.mxo + i.x()*mp.mxi + d*mp.mxd, o.y()*mp.myo + i.y()*mp.myi);
}

QSize Vectors::size(const Coeffs& mp) const
{
    return QSize(o.x()*mp.mxo + i.x()*mp.mxi + d*mp.mxd + 1, o.y()*mp.myo + i.y()*mp.myi + 1);
}

QRect Vectors::rect(const Coeffs& ofs, const Coeffs& siz) const
{
    return QRect(point(ofs), size(siz));
}
