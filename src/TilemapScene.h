#ifndef TILEMAPSCENE_H
#define TILEMAPSCENE_H

#include <QGraphicsScene>
#include <QGraphicsSceneMouseEvent>
#include "Graph.h"

const int GRID_SIZE = 30;
const QColor GRID_COLOR = QColor(200, 200, 255, 255);
const double FOREST_WEIGHT = 2;
const double WATER_WEIGHT = 5;
const QColor PATH_COLOR = QColor(250, 240, 65, 150);

/**
 * @brief The TilemapScene class is responsible for the visual representation of
 * a grid graph in a graphics view and its modification via the user input on the view.
 */
class TilemapScene : public QGraphicsScene
{
public:
    enum Algorithm{A_STAR, DIJKSTRA, BFS, GREEDY_BEST_FIRST};

public:
    /**
     * @brief Constructs a grid of size x size tiles, and represents it on
     * the view.
     *
     * The grid graph used will have top-left coordinates of (-size/2, -size/2), and
     * have a width and height of size, so the bottom-right coordinates will be
     * (size/2, size/2).
     *
     * Initially, the start tile is set to (0, 0), and the goal tile to (3, 3).
     */
    TilemapScene(QObject *parent, int size);

    /**
     * @brief Updates the currently active weight and color for painting tiles.
     *
     * When the user paints a tile by clicking it, this color and weight will be used
     * to update both the visual representation and the actual cost of the tile in the
     * grid graph.
     *
     * @param color Color to set as active.
     * @param weight Weight to set as active.
     */
    void setSelectedTileType(QColor color, double weight);

    /**
     * @brief Sets the currently active algorithm to be used for the path computation.
     * @param index Index of the algorithm combo box in the main window, which maps to
     * an algorithm via the Algorithm enum.
     */
    void setAlgorithm(int index);

    /**
     * @brief Sets whether or not the costs of explored tiles should be shown on top of
     * the tiles.
     *
     * Also triggers a path recomputation.
     */
    void setShowCost(bool state);

    /**
     * @brief Resets the map state to the initial one.
     *
     * Effectively removes all weights from the graph and resets the start and goal positions.
     */
    void reset();

private slots:
    void mousePressEvent(QGraphicsSceneMouseEvent *ev);
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *ev);
    void mouseMoveEvent(QGraphicsSceneMouseEvent *ev);

protected:
    void drawBackground(QPainter *painter, const QRectF &rect);
    void drawForeground(QPainter *painter, const QRectF &rect);

private:
    /**
     * @brief Updates the cost of a tile in the grid with the currently active weight,
     * and paints the visual representation of the tile with the given color.
     * @param tile Tile in the grid graph to update.
     * @param color Color to be used to paint the visual representation of the tile.
     */
    void paintTile(const Tile &tile, const QColor &color);

    /**
     * @brief Places a pixmap item on top of the visual representation of the given tile.
     * @param item Pointer to the pixmap item to be placed.
     * @param tile Tile in the grid graph where the pixmap should be placed.
     *
     * The placement of the pixmap tile will have no effect on the grid graph itself,
     * only on the visual representation of the tile.
     */
    void movePixmapToTile(QGraphicsPixmapItem *item, Tile tile);

    /**
     * @brief Recomputes the path using the currently selected algorithm and draws it.
     *
     * Any old path representation is cleared first, and then the new path is computed
     * using the pertinent algorithm and drawn on the screen.
     */
    void recomputePath();

    /**
     * @brief Paints a path given as a list of tiles using the color defined by a
     * constant.
     *
     * Keeps track of the painted items in a private variable, so that the drawn path
     * can be cleared later.
     */
    void paintPath(std::vector<Tile> path);

    /**
     * @brief Clears any painted path on the view.
     */
    void clearPath();

    /**
     * @brief Given a costs map like the one used in the pathfinding algorithms, paints
     * the cost to reach each tile on the visual representation with text.
     *
     * Keeps track of the painted items in a private variable, so that the cost text can be
     * cleared later.
     */
    void paintTileCosts(std::map<Tile, double> &costs);

    /**
     * @brief Clears any cost text on any tiles in the visual representation.
     */
    void clearText();

    /**
     * @brief Initializes the scene with the preset positions for start and goal points
     * and all tiles as floor.
     */
    void init();

private:
    int size;
    bool painting;
    QColor selectedColor;
    double selectedWeight;
    GridGraph graph;
    Tile startTile, goalTile;
    QGraphicsPixmapItem *startPixmap, *goalPixmap, *grabbedPixmap;
    std::vector<QGraphicsRectItem*> pathRects;
    Algorithm selectedAlgorithm;
    std::vector<QGraphicsSimpleTextItem*> tileTexts;
    bool showCost;
};

#endif // TILEMAPSCENE_H
