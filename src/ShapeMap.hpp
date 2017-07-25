#ifndef CNBIDRAW_SHAPE_MAP_HPP
#define CNBIDRAW_SHAPE_MAP_HPP

#include <map>
#include <unordered_map>

#include "Flags.hpp"
#include "Shape.hpp"

namespace cnbi {
	namespace draw {

typedef std::unordered_map<std::string, Shape*> MShape;
typedef std::unordered_map<std::string, Shape*>::iterator MShapeIt;

typedef std::map<unsigned int, std::string> MOrder;
typedef std::map<unsigned int, std::string>::iterator MOrderIt;
typedef std::map<unsigned int, std::string>::reverse_iterator MOrderRIt;

/*! \brief ShapeMap class
 *
 * This class represents an organized containers for Shape objects. It
 * implements methods to add/remove and organize the shapes. It is directly used
 * by the Engine to keep track of the shapes to be drawn. Essentially, the class
 * has two internal maps: an unordered map with the pointers to the shapes and
 * an ordered map with the position. The internal position maps is used to
 * manage the order of the shapes when they are drawn by means of the provided
 * iterators. It automatically manages the two internal maps, without any burden
 * for the user. The container is not thread-safe. The user needs to take care
 * of protecting the data if multi-thread application is used.
 *
 * \sa Shape, Engine
 */
class ShapeMap {
	
	public:
		/*! \brief Constructor
		 */
		ShapeMap(void);
		
		/*! \brief Destructor
		 */
		~ShapeMap(void);

		/*! \brief Add a new shape to the container
		 *
		 * It adds a new shape shp to the container. By default, it will have
		 * the highest order.
		 *
		 * \param	name	Shape's name
		 * \param	shp		Shape's pointer
		 *
		 * \return	True if the shape is added, false otherwise
		 */
		bool Emplace(const std::string& name, Shape* shp);
		
		/*! \brief Remove the shape from the container
		 *
		 * It removes the shape identified by the id name from the container.
		 * The order of the other shapes is automatically updated.
		 *
		 * \param	name	Shape's name
		 *
		 * \return	True if the shape is removed, false otherwise
		 */
		bool Erase(const std::string& name);
		
		/*! \brief Check if a shape exists
		 *
		 * It checks if the shaped identified by the id name exists in the
		 * container.
		 *
		 * \return	True if the shape exists, false otherwise
		 */
		bool Exists(const std::string& name);
		
		/*! \brief Number of shapes in the container
		 *
		 * It returns the number of shapes in the container (size of the
		 * container).
		 *
		 * \return	Number of shapes
		 */
		unsigned int Size(void);
		
		/*! \brief Check if the container is empty
		 *
		 * It checks if the container has no shapes inside.
		 *
		 * \return	True if it is empty, false otherwise
		 */
		bool Empty(void);
		
		/*! \brief Switch the position between two shapes
		 *
		 * It switches the position (order) of the two shapes identified by name1
		 * and name2
		 *
		 * \param	name1	Name of the first shape
		 * \param	name2	Name of the second shape
		 *
		 * \return	True if the switch occurs, false otherwise
		 */
		bool SwitchPosition(const std::string& name1, const std::string& name2);
		
		/*! \brief Switch the position between two shapes
		 *
		 * It switches the position (order) of the two shapes identified the
		 * iterators it1 and it2.
		 *
		 * \param	it1		Iterator pointing to the first shape element
		 * \param	it2		Iterator pointing to the second shape element
		 *
		 * \return	True if the switch occurs, false otherwise
		 */
		bool SwitchPosition(MOrderIt it1, MOrderIt it2);
		
		/*! \brief Bring the shape one position up
		 *
		 * It brings one position up the shape identified by name
		 *
		 * \param	name	Shape's identifier
		 *
		 * \return	True if the switch occurs, false otherwise
		 */
		bool Up(const std::string& name);
		
		/*! \brief Bring the shape one position down
		 *
		 * It brings one position down the shape identified by name
		 *
		 * \param	name	Shape's identifier
		 *
		 * \return	True if the switch occurs, false otherwise
		 */
		bool Down(const std::string& name);
		
		/*! \brief Bring the shape at the top position
		 *
		 * It brings the shape identified by name at the top position in the
		 * container.
		 *
		 * \param	name	Shape's identifier
		 *
		 * \return	True if the switch occurs, false otherwise
		 */
		bool Top(const std::string& name);
		
		/*! \brief Bring the shape at the bottom position
		 *
		 * It brings the shape identified by name at the bottom position in the
		 * container.
		 *
		 * \param	name	Shape's identifier
		 *
		 * \return	True if the switch occurs, false otherwise
		 */
		bool Bottom(const std::string& name);

		/*! \brief Find the shape
		 *
		 * It looks for the shape with the name identifier 
		 *
		 * \param	name	Shape's identifier
		 *
		 * \return	Iterator to the shape element if exists, or to the end of
		 * the container otherwise
		 */
		MShapeIt FindShape(const std::string& name);
		
		/*! \brief Find the shape order
		 *
		 * It looks for the position of the shape with the name identifier 
		 *
		 * \param	name	Shape's identifier
		 *
		 * \return	Iterator to the position of the shape if exists, or to the end of
		 * the container otherwise
		 */
		MOrderIt FindOrder(const std::string& name);
		
		/*! \brief Find the shape order
		 *
		 * It looks for the shape at the given position
		 *
		 * \param	key	Shape's position
		 *
		 * \return	Iterator to the element at the position if exists, or to the end of
		 * the container otherwise
		 */
		MOrderIt FindOrder(const unsigned int key);
		
		/*! \brief Consolidate shapes' positions
		 *
		 * It recompute the position of all the shapes in the container, by
		 *removing possible empty positions.
		 *
		 */
		void Consolidate(void);
		
		/*! \brief Dump elements in the container
		 *
		 */
		void Dump(void);
		
		/*! \brief Map-like begin method
		 *
		 * It returns an iterator to the begin of the container
		 *
		 * \return Iterator (<std::string, Shape*>)
		 */
		MShapeIt  BeginShape(void);
		
		/*! \brief Map-like end method
		 *
		 * It returns an iterator to the end of the container
		 *
		 * \return Iterator (<std::string, Shape*>)
		 */
		MShapeIt  EndShape(void);

		/*! \brief Map-like begin method
		 *
		 * It returns an iterator to the begin of the container
		 *
		 * \return Iterator (<unsigned int, std::string>)
		 */
		MOrderIt  BeginOrder(void);
		
		/*! \brief Map-like end method
		 *
		 * It returns an iterator to the end of the container
		 *
		 * \return Iterator (<unsigned int, std::string>)
		 */
		MOrderIt  EndOrder(void);
		
		/*! \brief Map-like reverse begin method
		 *
		 * It returns an iterator to the begin of the container starting from
		 * the end
		 *
		 * \return Iterator (<unsigned int, std::string>)
		 */
		MOrderRIt RBeginOrder(void);
		
		/*! \brief Map-like reverse end method
		 *
		 * It returns an iterator to the end of the container starting from
		 * the end
		 *
		 * \return Iterator (<unsigned int, std::string>)
		 */
		MOrderRIt REndOrder(void);
		
	private:

	private:
		MShape	map_shape_;
		MOrder	map_order_;

};

	}
}
#endif

