#include "Collider.h"
float BoxCollider::x() {
    return rect.getPosition().x;
}

float BoxCollider::y() {
    return rect.getPosition().y;
}

float BoxCollider::Left() {
    return x();
}

float BoxCollider::Right() {
    return x() + rect.getSize().x;
}

float BoxCollider::Top() {
    return y();
}

float BoxCollider::Bottom() {
    return y() + rect.getSize().y;
}

float CircleCollider::x() {
    return circle.getPosition().x;
}

float CircleCollider::y() {
    return circle.getPosition().y;
}

float CircleCollider::Left() {
    return x();
}

float CircleCollider::Right() {
    return x() + 2.f * circle.getRadius();
}

float CircleCollider::Top() {
    return y();
}

float CircleCollider::Bottom() {
    return y() + 2.f * circle.getRadius();
}


int Collide(Collider* a, Collider* b) {
    bool intersect = (
        (b->Left() < a->Right()) && (a->Left() < b->Right()) &&
        (b->Top() < a->Bottom()) && (a->Top() < b->Bottom())
        );

    if (!intersect) {
        return 0;
    }
    float overlapLeft = std::abs(b->Right() - a->Left());
    float overlapRight = std::abs(a->Right() - b->Left());
    float overlapTop = std::abs(a->Bottom() - b->Top());
    float overlapBottom = std::abs(b->Bottom() - a->Top());

    float minOverlapX = std::min(overlapLeft, overlapRight);
    float minOverlapY = std::min(overlapTop, overlapBottom);

    if (minOverlapX < minOverlapY) {
        return 1;
    }
    return -1;
}