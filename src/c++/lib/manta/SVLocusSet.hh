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

#pragma once

#include "manta/SVLocus.hh"

#include <iosfwd>
#include <map>
#include <vector>


// A set of non-overlapping SVLocus objects
//
struct SVLocusSet
{

    /// merge new locus into the set:
    ///
    /// locus is destroyed in this process
    ///
    void
    merge(SVLocus& locus);

    void
    write(std::ostream& os) const;

private:

    /// combine all content from loci from into to
    ///
    /// this is typically required when a node is merged
    /// which combines two loci
    void
    combineLoci(
            const unsigned fromIndex,
            const unsigned toIndex);



    typedef std::map<SVLocusNode*, unsigned> ins_type;


    // contains the full set of loci
    std::vector<SVLocus> _loci;

    // provides an intersection search of non-overlapping nodes:
    ins_type _inodes;
};