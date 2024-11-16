#include <gtest/gtest.h>
#include <memory>
#include "array.h"
#include "figure.h"
#include "rectangle.h"
#include "square.h"
#include "triangle.h"

TEST(ArrayTest, AddElements) {
    Array<Figure<int>> figures;

    std::shared_ptr<Figure<int>> rect = std::make_shared<Rectangle<int>>(5, 10);
    std::shared_ptr<Figure<int>> sq = std::make_shared<Square<int>>(5);
    std::shared_ptr<Figure<int>> triangle = std::make_shared<Triangle<int>>(5);

    figures.add(rect);
    figures.add(sq);
    figures.add(triangle);

    EXPECT_EQ(figures.size, 3);

    EXPECT_EQ(figures[0]->area(), 50);
    EXPECT_EQ(figures[1]->area(), 25);
    EXPECT_EQ(figures[2]->area(), 10);
}

TEST(ArrayTest, RemoveElement) {
    Array<Figure<int>> figures;

    std::shared_ptr<Figure<int>> rect = std::make_shared<Rectangle<int>>(5, 10);
    figures.add(rect);

    std::shared_ptr<Figure<int>> removed = figures.remove();
    EXPECT_EQ(figures.size, 0);
    EXPECT_EQ(removed->area(), 50);
}

TEST(ArrayTest, InsertElement) {
    Array<Figure<int>> figures;

    std::shared_ptr<Figure<int>> rect = std::make_shared<Rectangle<int>>(5, 10);
    std::shared_ptr<Figure<int>> sq = std::make_shared<Square<int>>(5);

    figures.add(rect);
    figures.add(sq);

    std::shared_ptr<Figure<int>> triangle = std::make_shared<Triangle<int>>(5);
    figures.insert(triangle, 0);

    EXPECT_EQ(figures[0]->area(), 10);
    EXPECT_EQ(figures[1]->area(), 50);
    EXPECT_EQ(figures[2]->area(), 25);
}

TEST(ArrayTest, PopElement) {
    Array<Figure<int>> figures;

    std::shared_ptr<Figure<int>> rect = std::make_shared<Rectangle<int>>(5, 10);
    figures.add(rect);

    std::shared_ptr<Figure<int>> popped = figures.pop(0);

    EXPECT_EQ(figures.size, 0);
    EXPECT_EQ(popped->area(), 50);
}

TEST(ArrayTest, OutOfRangeError) {
    Array<Figure<int>> figures;

    EXPECT_THROW(figures[0], IndexOutOfRangeException);

    EXPECT_THROW(figures.remove(), ArrayIsEmptyException);
}

TEST(ArrayTest, EqualityOperator) {
    Array<Figure<int>> figures1;
    Array<Figure<int>> figures2;

    std::shared_ptr<Figure<int>> rect1 = std::make_shared<Rectangle<int>>(5, 10);
    std::shared_ptr<Figure<int>> sq1 = std::make_shared<Square<int>>(5);

    figures1.add(rect1);
    figures1.add(sq1);

    std::shared_ptr<Figure<int>> rect2 = std::make_shared<Rectangle<int>>(5, 10);
    std::shared_ptr<Figure<int>> sq2 = std::make_shared<Square<int>>(5);

    figures2.add(rect2);
    figures2.add(sq2);

    EXPECT_TRUE(figures1 == figures2);

    std::shared_ptr<Figure<int>> triangle = std::make_shared<Triangle<int>>(5);
    figures2.add(triangle);

    EXPECT_TRUE(figures1 != figures2);
}

TEST(FigureTest, AreaTest) {
    std::shared_ptr<Figure<int>> rect = std::make_shared<Rectangle<int>>(5, 10);
    std::shared_ptr<Figure<int>> sq = std::make_shared<Square<int>>(5);
    std::shared_ptr<Figure<int>> triangle = std::make_shared<Triangle<int>>(5);

    EXPECT_EQ(rect->area(), 50);
    EXPECT_EQ(sq->area(), 25);
    EXPECT_EQ(triangle->area(), 10);
}
