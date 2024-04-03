#include "sdlms/physics.hpp"
#include <ranges>
#include <utility>
#include <algorithm>

Physics::Physics()
{
    _map = Map::current();
    _character = Character::current();
}

void Physics::update(int elapsedTime)
{
    auto fhs = _map->_foothold;

    float _elapsedTime = elapsedTime / 1000.0;

    // 垂直方向有力,默认质量为1
    _character->_hacc = _character->_hforce;
    _character->_vacc = _character->_vforce;

    auto _hspeed = _character->_hspeed + _elapsedTime * _character->_hacc;
    auto _vspeed = _character->_vspeed + _elapsedTime * _character->_vacc;

    Point<float> new_pos = _character->_pos + Point<float>{(_character->_hspeed + _hspeed) / 2 * _elapsedTime,
                                                           (_character->_vspeed + _vspeed) / 2 * _elapsedTime};

    _character->_hspeed += _elapsedTime * _character->_hacc;
    _character->_vspeed += _elapsedTime * _character->_vacc;

    _character->_vspeed = std::min(_character->_vspeed, 200.0f);
    _character->_hspeed = std::clamp(_character->_hspeed, -240.0f, 240.0f);

    // 地面碰撞检测
    if (_character->_ground == true)
    {
        auto x = new_pos.x();
        auto y = _fh.get_y(x);
        if (!y.has_value())
        {
            // 人物移动后x不在fh,切换fh,重写算出新的y坐标
            if (x < _fh._a.x() && x < _fh._b.x())
            {
                // 切换到左边fh
                if (fhs[_fh._prev]._type == FootHold::WALL)
                {
                    // 墙面或者悬崖
                    // 撞墙
                    x = fhs[_fh._prev].get_x(0).value();
                    //
                }
                else
                {
                    // 平地或者斜坡,切换fh,重写计算y值
                    _fh = fhs[_fh._prev];
                    y = _fh.get_y(x).value();
                }
            }
            if (x > _fh._a.x() && x > _fh._b.x())
            {
                // 切换到右边fh
                if (fhs[_fh._next]._type == FootHold::WALL)
                {
                    // 撞墙
                    x = fhs[_fh._next].get_x(0).value();
                }
                else
                {
                    // 平地或者斜坡,切换fh,重写计算y值
                    _fh = fhs[_fh._next];
                    y = _fh.get_y(x).value();
                }
            }
        }
        _character->_pos.set_y(y.value());
        _character->_pos.set_x(x);
        return;
    }
    else
    {
        // 空中碰撞检测
        for (auto [id, it] : fhs)
        {
            Point<float> p1 = {(float)it._a.x(), (float)it._a.y()};
            Point<float> p2 = {(float)it._b.x(), (float)it._b.y()};

            std::pair<const Point<float> &, const Point<float> &> l1(_character->_pos, new_pos);
            std::pair<const Point<float> &, const Point<float> &> l2(p1, p2);

            // 判断fh与人物是否相交
            auto r = segmentsIntersection(l1, l2);
            if (r.has_value())
            {
                // 修改坐标为交点
                _character->_pos = r.value();
                if (it._type == FootHold::WALL)
                {
                    // 从空中撞到墙
                    _character->_hspeed = 0.0f;
                }
                else
                {
                    // 撞到地板或者斜坡
                    _character->_ground = true;
                    _character->_vspeed = 0.0f;
                    _fh = it;
                }

                return;
            }
        }
        _character->_pos = new_pos;
    }
    return;
}

// 判断线段是否相交
template <typename T>
inline std::optional<Point<T>> Physics::segmentsIntersection(std::pair<const Point<T> &, const Point<T> &> a, std::pair<const Point<T> &, const Point<T> &> b)
{
    std::optional<Point<T>> intersection;

    auto [p1, p2] = a;
    auto [p3, p4] = b;
    // 快速排斥实验
    if ((p1.x() > p2.x() ? p1.x() : p2.x()) < (p3.x() < p4.x() ? p3.x() : p4.x()) ||
        (p1.y() > p2.y() ? p1.y() : p2.y()) < (p3.y() < p4.y() ? p3.y() : p4.y()) ||
        (p3.x() > p4.x() ? p3.x() : p4.x()) < (p1.x() < p2.x() ? p1.x() : p2.x()) ||
        (p3.y() > p4.y() ? p3.y() : p4.y()) < (p1.y() < p2.y() ? p1.y() : p2.y()))
    {
        return intersection;
    }
    // 跨立实验
    if ((((p1.x() - p3.x()) * (p4.y() - p3.y()) - (p1.y() - p3.y()) * (p4.x() - p3.x())) *
         ((p2.x() - p3.x()) * (p4.y() - p3.y()) - (p2.y() - p3.y()) * (p4.x() - p3.x()))) > 0 ||
        (((p3.x() - p1.x()) * (p2.y() - p1.y()) - (p3.y() - p1.y()) * (p2.x() - p1.x())) *
         ((p4.x() - p1.x()) * (p2.y() - p1.y()) - (p4.y() - p1.y()) * (p2.x() - p1.x()))) > 0)
    {
        return intersection;
    }

    auto x = ((p1.y() - p3.y()) * (p2.x() - p1.x()) * (p4.x() - p3.x()) + p3.x() * (p4.y() - p3.y()) * (p2.x() - p1.x()) - p1.x() * (p2.y() - p1.y()) * (p4.x() - p3.x())) / ((p4.x() - p3.x()) * (p1.y() - p2.y()) - (p2.x() - p1.x()) * (p3.y() - p4.y()));
    auto y = (p2.y() * (p1.x() - p2.x()) * (p4.y() - p3.y()) + (p4.x() - p2.x()) * (p4.y() - p3.y()) * (p1.y() - p2.y()) - p4.y() * (p3.x() - p4.x()) * (p2.y() - p1.y())) / ((p1.x() - p2.x()) * (p4.y() - p3.y()) - (p2.y() - p1.y()) * (p3.x() - p4.x()));

    intersection.emplace(Point<float>{x, y});

    return intersection;
}
