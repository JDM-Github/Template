#pragma once
#ifndef JDM_STRUCT_HPP
#define JDM_STRUCT_HPP
#include "defines.hpp"

/**
 * @namespace JDM
 * @brief Contains utility structures and types for the JDM library.
 *
 * The `JDM` namespace provides various utility structures and types that are commonly used
 * within the JDM library. These structures include positions, sizes, colors, regions, arcs,
 * and line points, which are used to represent graphical properties and measurements.
 */
JNAMESPACE JDM
{
    /**
     * @struct Position
     * @brief Represents a 2D position with X and Y coordinates.
     */
    JSTRUCT Position
    {
        JDOUBLE x; /**< The X coordinate of the position. */
        JDOUBLE y; /**< The Y coordinate of the position. */
    };

    /**
     * @struct Size
     * @brief Represents a 2D size with width and height dimensions.
     */
    JSTRUCT Size
    {
        JDOUBLE width;  /**< The width dimension of the size. */
        JDOUBLE height; /**< The height dimension of the size. */
    };

    /**
     * @struct PositionSize
     * @brief Represents a combination of position and size.
     *
     * The `PositionSize` structure provides a convenient way to represent a position
     * and size together, allowing the use of either individual properties or a combined
     * position-size representation.
     */
    JSTRUCT PositionSize
    {
        JUNION
        {
            JSTRUCT
            {
                JDOUBLE x;      /**< The X coordinate of the position. */
                JDOUBLE y;      /**< The Y coordinate of the position. */
                JDOUBLE width;  /**< The width dimension of the size. */
                JDOUBLE height; /**< The height dimension of the size. */
            };
            JSTRUCT
            {
                JDM::Position pos; /**< The position. */
                JDM::Size     size;    /**< The size. */
            };
        };
    };

    /**
     * @struct ColorRGB
     * @brief Represents a color in RGB format with red, green, and blue channels.
     */
    JSTRUCT ColorRGB
    {
        JUINT8 r; /**< The red channel value. */
        JUINT8 g; /**< The green channel value. */
        JUINT8 b; /**< The blue channel value. */
        JUINT8 a; /**< The alpha channel value (opacity). */
    };

    /**
     * @struct ColorRGBA
     * @brief Represents a color in RGBA format with red, green, blue, and alpha channels.
     *
     * The `ColorRGBA` structure provides a convenient way to represent a color with RGB
     * channels and an additional alpha channel for opacity control.
     */
    JSTRUCT ColorRGBA
    {
        JUNION
        {
            JSTRUCT
            {
                JUINT8 r;         /**< The red channel value. */
                JUINT8 g;         /**< The green channel value. */
                JUINT8 b;         /**< The blue channel value. */
                JUINT8 a;         /**< The alpha channel value (opacity). */
            };
            JSTRUCT
            {
                JDM::ColorRGB rgb; /**< The RGB color. */
                JUINT8        opacity;    /**< The alpha channel value (opacity). */
            };
        };
    };

    /**
     * @struct Region
     * @brief Represents a rectangular region with X and Y coordinates, width, and height.
     */
    JSTRUCT Region
    {
        JINT x; /**< The X coordinate of the region. */
        JINT y; /**< The Y coordinate of the region. */
        JINT w; /**< The width dimension of the region. */
        JINT h; /**< The height dimension of the region. */
    };
    /**
     * @struct RegionF
     * @brief Represents a rectangular region with floating-point coordinates, width, and height.
     */
    JSTRUCT RegionF
    {
        JFLOAT x; /**< The X coordinate of the region. */
        JFLOAT y; /**< The Y coordinate of the region. */
        JFLOAT w; /**< The width dimension of the region. */
        JFLOAT h; /**< The height dimension of the region. */
    };

    /**
     * @struct LinePoints
     * @brief Represents the coordinates of two points defining a line segment.
     */
    JSTRUCT LinePoints
    {
        JDOUBLE x1; /**< The X coordinate of the first point. */
        JDOUBLE y1; /**< The Y coordinate of the first point. */
        JDOUBLE x2; /**< The X coordinate of the second point. */
        JDOUBLE y2; /**< The Y coordinate of the second point. */
    };

    /**
     * @struct FourArc
     * @brief Represents the four arc values for the corners of a rectangle.
     *
     * The `FourArc` structure stores arc values for the top left, top right, bottom left,
     * and bottom right corners of a rectangle. These arc values determine the roundness
     * of the corners when drawing shapes or creating curved edges.
     */
    JSTRUCT FourArc
    {
        JUINT8 topLeft;     /**< The arc value for the top left corner. */
        JUINT8 topRight;    /**< The arc value for the top right corner. */
        JUINT8 bottomLeft;  /**< The arc value for the bottom left corner. */
        JUINT8 bottomRight; /**< The arc value for the bottom right corner. */

        FourArc(JCINT tL, JCINT tR, JCINT bL, JCINT bR)
        {
            JTHIS->topLeft     = tL;
            JTHIS->topRight    = tR;
            JTHIS->bottomLeft  = bL;
            JTHIS->bottomRight = bR;
        }

        FourArc(JCONST ColorRGB& color)
        {
            JTHIS->topLeft     = color.r;
            JTHIS->topRight    = color.g;
            JTHIS->bottomLeft  = color.b;
            JTHIS->bottomRight = color.a;
        }
    };

    /**
     * @struct TwoLRArc
     * @brief Represents the arc values for the left and right corners of a shape or object.
     *
     * The `TwoLRArc` structure stores arc values for the left and right corners of a shape
     * or object. These arc values determine the roundness of the corners when drawing shapes
     * or creating curved edges.
     */
    JSTRUCT TwoLRArc
    {
        JUINT8 leftArc;  /**< The arc value for the left corner. */
        JUINT8 rightArc; /**< The arc value for the right corner. */
    };

    /**
     * @struct TwoTBArc
     * @brief Represents the arc values for the top and bottom corners of a shape or object.
     *
     * The `TwoTBArc` structure stores arc values for the top and bottom corners of a shape
     * or object. These arc values determine the roundness of the corners when drawing shapes
     * or creating curved edges.
     */
    JSTRUCT TwoTBArc
    {
        JUINT8 topArc;    /**< The arc value for the top corner. */
        JUINT8 bottomArc; /**< The arc value for the bottom corner. */
    };
}

#endif