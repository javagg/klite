#include <QFile>
#include <QTemporaryFile>
#include <QTemporaryDir>
#include "dbStream.h"
#include "dbReader.h"
#include "dbGDS2Reader.h"
#include "dbGDS2Writer.h"

QString extractResourceToTemp(const QString &resourcePath, const QString &fileName);

class GDS2FormatDeclaration
    : public db::StreamFormatDeclaration
{
    virtual std::string format_name () const { return "GDS2"; }
    virtual std::string format_desc () const { return "GDS2"; }
    virtual std::string format_title () const { return "GDS2"; }
    virtual std::string file_format () const { return "GDS2 files (*.gds *.GDS *.gds.gz *.GDS.gz *.GDS2 *.gds2 *.gds2.gz *.GDS2.gz)"; }

    virtual bool detect (tl::InputStream &stream) const
    {
        const char *hdr = stream.get (4);
        return (hdr && hdr[0] == 0x00 && hdr[1] == 0x06 && hdr[2] == 0x00 && hdr[3] == 0x02);
    }

    virtual db::ReaderBase *create_reader (tl::InputStream &s) const
    {
        return new db::GDS2Reader (s);
    }

    virtual db::WriterBase *create_writer () const
    {
        return new db::GDS2Writer ();
    }

    virtual bool can_read () const
    {
        return true;
    }

    virtual bool can_write () const
    {
        return true;
    }

    virtual tl::XMLElementBase *xml_writer_options_element () const
    {
        return new db::WriterOptionsXMLElement<db::GDS2WriterOptions> ("gds2",
                                                                      tl::make_member (&db::GDS2WriterOptions::write_timestamps, "write-timestamps") +
                                                                          tl::make_member (&db::GDS2WriterOptions::write_cell_properties, "write-cell-properties") +
                                                                          tl::make_member (&db::GDS2WriterOptions::write_file_properties, "write-file-properties") +
                                                                          tl::make_member (&db::GDS2WriterOptions::no_zero_length_paths, "no-zero-length-paths") +
                                                                          tl::make_member (&db::GDS2WriterOptions::default_text_size, "default-text-size") +
                                                                          tl::make_member (&db::GDS2WriterOptions::multi_xy_records, "multi-xy-records") +
                                                                          tl::make_member (&db::GDS2WriterOptions::resolve_skew_arrays, "resolve-skew-arrays") +
                                                                          tl::make_member (&db::GDS2WriterOptions::max_vertex_count, "max-vertex-count") +
                                                                          tl::make_member (&db::GDS2WriterOptions::max_cellname_length, "max-cellname-length") +
                                                                          tl::make_member (&db::GDS2WriterOptions::libname, "libname")
                                                                      );
    }

    virtual tl::XMLElementBase *xml_reader_options_element () const
    {
        return new db::ReaderOptionsXMLElement<db::GDS2ReaderOptions> ("gds2",
                                                                      tl::make_member (&db::GDS2ReaderOptions::box_mode, "box-mode") +
                                                                          tl::make_member (&db::GDS2ReaderOptions::allow_big_records, "allow-big-records") +
                                                                          tl::make_member (&db::GDS2ReaderOptions::allow_multi_xy_records, "allow-multi-xy-records")
                                                                      );
    }
};

