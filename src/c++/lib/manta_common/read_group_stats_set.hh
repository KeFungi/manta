// -*- mode: c++; indent-tabs-mode: nil; -*-
//
// Manta
// Copyright (c) 2013 Illumina, Inc.
//
// This software is provided under the terms and conditions of the
// Illumina Open Source Software License 1.
//
// You should have received a copy of the Illumina Open Source
// Software License 1 along with this program. If not, see
// <https://github.com/downloads/sequencing/licenses/>.
//
/**
 ** Copyright (c) 2007-2010 Illumina, Inc.
 **
 ** This software is covered by the "Illumina Genome Analyzer Software
 ** License Agreement" and the "Illumina Source Code License Agreement",
 ** and certain third party copyright/licenses, and any user of this
 ** source file is bound by the terms therein (see accompanying files
 ** Illumina_Genome_Analyzer_Software_License_Agreement.pdf and
 ** Illumina_Source_Code_License_Agreement.pdf and third party
 ** copyright/license notices).
 **
 ** This file is part of the Guided Reassembly Of Unaligned Paired-End Reads
 ** (GROUPER) software package.
 **
 **/

#pragma once

#include "blt_util/id_map.hh"
#include "manta_common/read_group_stats.hh"

#include <iosfwd>
#include <string>

#include "boost/optional.hpp"



/// \brief manages multiple read_group_stats
///
struct read_group_stats_set {

    /// \brief get the index of a read group
    ///
    /// the index can be used for fast lookup of the
    /// stats for that group
    ///
    /// if the group does not exist, the returned value
    /// evaluates to false per boost::optional
    ///
    /// for now, a "read group" is fixed to the name of
    /// each bam file
    boost::optional<unsigned>
    get_group_index(const std::string& bam_file) const {
        return _group.get_optional_id(bam_file);
    }

    /// get stats associated with index
    const read_group_stats&
    get_stats(const unsigned group_index) const {
        return _group.get_value(group_index);
    }

    /// set stats for index
    void
    set_stats(const std::string& bam_file,
              const read_group_stats& rps) {
        _group.insert(bam_file,rps);
    }

    //
    // persistence:
    //
    void
    store(std::ostream& os) const;

    void
    load(std::istream& os);

private:
    void
    clear() {
        _group.clear();
    }

    id_map<std::string, read_group_stats> _group;
};
