#include <algorithm>

#include <gtest/gtest.h>

// FUGLY :)
#include "../../libmonadic/include/monadic.hpp"
#include "../../libmonadic/include/object.hpp"
#include "../../libmonadic/include/objects/image/image.hpp"

using namespace monadic;

TEST(object_serialization, image)
{
    Image* img1 = new Image();
    img1->create( 1600, 1200, 8, 3 );
    img1->ptr()[47] = 7;
    unsigned int N = 100;
    for( int k = 0; k < N; ++k )
    {
        Image* img2 = new Image();
        ObjectBlob* blob = img1->serialize();
        img2->deserialize(blob);
        EXPECT_EQ( img2->ptr()[47], 7 );
        delete img2;
        delete blob;
    }
}
