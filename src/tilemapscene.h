#ifndef TILEMAPSCENE_H
#define TILEMAPSCENE_H

#include <QGraphicsScene>
#include <QGraphicsSceneMouseEvent>
#include "gridgraph.h"

const int GRID_SIZE = 30;
const QColor GRID_COLOR = QColor(200, 200, 255, 255);
const QColor FLOOR_COLOR = QColor(Qt::white);
const QColor WALL_COLOR = QColor(Qt::black);
const double FOREST_WEIGHT = 2;
const QColor FOREST_COLOR = QColor(Qt::green);
const double WATER_WEIGHT = 5;
const QColor WATER_COLOR = QColor(Qt::blue);
const QColor CUSTOM_WEIGHT_COLOR = QColor(Qt::gray);
const QColor PATH_COLOR = QColor(250, 240, 65, 255);

/**
 * @brief The TilemapScene class is responsible for the visual representation of
 * a grid graph in a graphics view and its modification via the user input on the view.
 */
class TilemapScene : public QGraphicsScene
{
public:
    enum eAlgorithm {A_STAR, DIJKSTRA, BFS, GREEDY_BEST_FIRST};
    enum eHeuristic {MANHATTAN, EUCLIDEAN, CHEBYSHEV, OCTILE};
    enum ePaintMode {PENCIL, BUCKET, LINE, RECT};

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
    TilemapScene(QObject *parent, int width, int height);

    /**
     * @brief Constructs a new scene using the provided graph
     */
    TilemapScene(QObject *parent, GridGraph *newGraph, Tile &start, Tile &goal);

    ~TilemapScene();

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
     * @brief Sets the currently active heuristic, for the algorithms that use one.
     * @param index Index of the heuristic combo box in the main window, which maps to
     * an heuristic via the Heuristic enum.
     */
    void setHeuristic(int index);

    /**
     * @brief Sets whether or not the costs of explored tiles should be shown on top of
     * the tiles.
     *
     * Also triggers a path recomputation.
     */
    void setShowCost(bool state);

    /**
     * @brief Sets whether or not diagonal movement is allowed
     */
    void setDiagonal(bool state);

    /**
     * @brief Sets whether or not corner movement is allowed
     */
    void setCornerMovement(bool state);

    /**
     * @brief Resets the map state to the initial one.
     *
     * Effectively removes all weights from the graph and resets the start and goal positions.
     */
    void reset();

    /**
     * @brief Switch between boring and goofy icons.
     */
    void setGoofyIcons(bool state);

    /**
     * @brief Sets whether or not the grid should be drawn.
     */
    void setShowGrid(bool state);

    /**
     * @brief Sets the currently active paint mode.
     * @param mode Paint mode to be used when the user left-clicks a tile.
     */
    void setPaintMode(ePaintMode mode);

    void saveGraphToFile(std::string filename);

    QPoint getStartPointPosition();

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
     * @return true if the tile was actually painted, false otherwise, for example, if
     * the tile already had the selected weight/color.
     */
    void paintTile(const Tile &tile, const QColor &color);

    bool updateTileWeight(const Tile &tile);

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

    /**
     * @brief Initializes the scene with the preset positions for start and goal points
     * but using the given graph as the scene graph.
     */
    void init(GridGraph *newGraph, Tile &start, Tile &goal);

    /**
     * @brief Paint all similar tiles in an enclosed region.
     */
    void bucketPaint(const Tile &tile);

    /**
     * @brief Clears the current tile painting preview from the screen and the buffer.
     */
    void clearPreview();

    /**
     * @brief Paint the preview tiles in the buffer, without updating weights.
     */
    void paintPreview(const QColor &color);

    /**
     * @brief Paint a line from start to end using Bresenham's line algorithm, but don't
     * update the weights yet.
     */
    void previewLinePaint(const Tile &start, const Tile &end, const QColor &color);

    /**
     * @brief Paint a rect with the given top-left and bottom-right corners, including them,
     * but don't update the weights yet.
     */
    void previewRectPaint(const Tile &topLeft, const Tile &bottomRight, const QColor &color);

    /**
     * @brief Actually paints the current preview, updating the weights.
     */
    void commitPreview();

    /**
     * @brief Sets up the pixmap on their default positions.
     */
    void setUpEndpoints(Tile start = Tile{0, 0}, Tile goal = Tile{3, 3});

    /**
     * @brief Clears the entire scene and repaints tiles that have weights on them, and resets
     * pixmaps to their original positions.
     */
    void repaintScene();

private:
    int width, height;
    bool painting, paintingLine, paintingRect;
    QColor selectedColor;
    double selectedWeight;
    GridGraph *graph;
    Tile startTile, goalTile, previousPosition;
    QGraphicsPixmapItem *startPixmap, *goalPixmap, *grabbedPixmap;
    std::vector<QGraphicsLineItem*> pathLines;
    eAlgorithm selectedAlgorithm;
    eHeuristic selectedHeuristic;
    std::vector<QGraphicsSimpleTextItem*> tileTexts;
    bool showCost, showGrid;
    ePaintMode paintMode;
    Tile previewOrigin;
    std::vector<Tile> previewTiles;
    std::vector<QGraphicsRectItem*> previewRects;
};

#endif // TILEMAPSCENE_H
