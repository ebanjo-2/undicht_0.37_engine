#ifndef XML_ELEMENT_H
#define XML_ELEMENT_H



namespace undicht {


    class XmlElement {

        public:
            // the data a xml element can store
            std::string m_tag_name;
            std::vector<std::string> m_tag_attributes;
            std::string m_content;

            // each element can contain multiple child elements
            std::vector<XmlElement> m_child_elements;


        public:
            // functions to access the data stored in the element

            /// @return whether the element has all the attributes (might have more)
            bool hasAttributes(const std::vector<std::string>& tag_attributes) const;

            /// @return the content stored between the start and end tag of the element (excluding child elements)
            const std::string& getContent() const;

            /** @return the first xml element that has all the requested tag attributes
            * @example for a tag attribute "<texture name="normal">"
            * @example tag attributes can be negated using a "!=" : "<texture name!="normal" name!="color" >"
            * will return the first texture element that has not the "name" normal
            * this way all child elements with certain attributes can be retrieved
            * (for more then one attribute passed) the found element will be searched for a child element that has the next attributes */
            const XmlElement& getElement(const std::vector<std::string>& attributes);


        public:

            XmlElement();
            virtual ~XmlElement();


    };

} // undicht

#endif // XML_ELEMENT_H
