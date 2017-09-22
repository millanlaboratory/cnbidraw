#ifndef CNBIDRAW_GALLERY_HPP
#define CNBIDRAW_GALLERY_HPP

#include <string>
#include <memory>
#include <vector>
#include <algorithm>
#include <dirent.h>
#include "Image.hpp"
#include "Flags.hpp"

namespace cnbi {
    namespace draw {

typedef std::vector<std::string>::iterator GalleryIt;

/*! \brief Gallery class
 *
 * Implements a gallery of images.
 */
class Gallery : public Image {

	public: 
		/*! \brief Constructor
		 * Instanciate the gallery at position (0,0) with the given frame size
		 *
		 * \param	width	Gallery's frame width
		 * \param	height	Gallery's frame height
		 */
		Gallery(float width, float height);
		
		/*! \brief Destructor
		 */
		virtual ~Gallery(void);

		/*! \brief Setting the source folder
		 * It set the current source folder for the gallery. It checks for file
		 * with the given extensions. In addition, it set the gallery iterator
		 * to the first image in the folder.
		 *
		 * \param	folder	Folder path 
		 * \param	exts	Standard vector with the allowed extensions
		 * \return	True if the folder exists and it can access to it. False
		 *			otherwise
		 *
		 */ 
		bool SetFolder(const std::string& folder, const std::vector<std::string> exts);

		/*! \brief The number of images in the gallery
		 * It returns the number of the image in the gallery
		 *
		 * \return	Number of images in the gallery
		 *
		 */ 
		size_t Size(void);

		/*! \brief Select (display) the current image
		 * It selects and display the image currently pointed by the internal
		 * iterator.
		 *
		 * \return True if the image is selected and displayed. False if the
		 * iterator reached the end of the list of images or if the image cannot
		 * be loaded.
		 */ 
		bool Select(void);
		
		/*! \brief Select (display) the image with the given index 
		 * It selects and display the image with the given index. The internal
		 * iterator is not updated to that position.
		 *
		 * \return True if the image is selected and displayed. False if the
		 * iterator reached the end of the list of images or if the image cannot
		 * be loaded.
		 */ 
		bool Select(unsigned int id);
		
		/*! \brief Select (display) the image pointed by the given iterator 
		 * It selects and display the image with the given index. The internal
		 * iterator is not updated to that position.
		 *
		 * \return True if the image is selected and displayed. False if the
		 * iterator reached the end of the list of images or if the image cannot
		 * be loaded.
		 */ 
		bool Select(GalleryIt it);

		/*! \brief Move to the next image
		 * It moves the internal operator to the next image. The image is not
		 * displayed until Select() method is called.
		 *
		 * \return True if the iterator did not reach the end of the images list
		 */
		bool Next(void);
		
		/*! \brief Move to the previous image
		 * It moves the internal operator to the previous image. The image is
		 * not displayed until Select() method is called.
		 *
		 * \return True if the iterator did not reach the begin of the images
		 * list
		 */
		bool Previous(void);
		
		/*! \brief Rewind the iterator
		 * It moves the internal operator to the first image. The image is
		 * not displayed until Select() method is called.
		 *
		 * \return True
		 */
		bool Rewind(void);
		
		/*! \brief Move the iterator to a image
		 * It moves the internal operator to the given image position. The image
		 * is not displayed until Select() method is called.
		 *
		 * \return True
		 */
		bool GoTo(GalleryIt it);
		
		/*! \brief Current iterator
		 *
		 * \return An iterator to the current position
		 */
		GalleryIt Current(void);
		
		/*! \brief Iterator to the begin
		 *
		 * \return An iterator to the beginning of the images lists
		 */
		GalleryIt Begin(void);
		
		/*! \brief Iterator to the end
		 *
		 * \return An iterator to the end of the images lists
		 */
		GalleryIt End(void);

	protected:
		bool HasExtension(const std::string& name, const std::string& ext);


	private:
		std::vector<std::string>	list_;
		GalleryIt	current_;
		std::string	folder_;

};

	}
}

#endif

