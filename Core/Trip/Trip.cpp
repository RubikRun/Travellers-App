#include "Trip.hpp"
#include "../Database/DatabaseIO.hpp"
#include "../../UI/UI.hpp"

Trip::Trip(){}

Trip::Trip(const str& dest, const Date& begin, const Date& end,
    int grade, const str& comment, const std::vector<str>& photos)
        : m_dest(dest), m_begin(begin), m_end(end), m_grade(grade), 
        m_comment(comment), m_photos(photos) {}

void Trip::SerializeTo(std::ostream& stream) const
{
    nDatabaseIO::WriteStr(m_dest, stream);
    m_begin.SerializeTo(stream);
    m_end.SerializeTo(stream);
    nDatabaseIO::WriteInt(m_grade, stream);
    nDatabaseIO::WriteStr(m_comment, stream);

    nDatabaseIO::WriteInt(m_photos.size(), stream);
    for (int i = 0; i < m_photos.size(); i++)
    {
        nDatabaseIO::WriteStr(m_photos[i], stream);
    }
}

void Trip::DeserializeFrom(std::istream& stream)
{
    m_dest = nDatabaseIO::ReadStr(stream);
    m_begin.DeserializeFrom(stream);
    m_end.DeserializeFrom(stream);
    m_grade = nDatabaseIO::ReadInt(stream);
    m_comment = nDatabaseIO::ReadStr(stream);

    int photosCount = nDatabaseIO::ReadInt(stream);
    m_photos = std::vector<str>(photosCount);
    for (int i = 0; i < photosCount; i++)
    {
        m_photos[i] = nDatabaseIO::ReadStr(stream);
    }
}

str Trip::ToStr() const
{
    str result;

    result += nMsg::nTrip::DEST + m_dest + "\n";
    result += nMsg::nTrip::BEGIN_DATE + m_begin.ToStr() + "\n";
    result += nMsg::nTrip::END_DATE + m_end.ToStr() + "\n";
    result += nMsg::nTrip::GRADE + std::to_string(m_grade) + "\n";
    result += nMsg::nTrip::COMMENT + m_comment + "\n";
    result += nMsg::nTrip::PHOTOS;

    for (int i = 0; i < m_photos.size(); i++)
    {
        result += m_photos[i];
        if (i < m_photos.size() - 1)
        {
            result += " ";
        }
    }

    return result;
}