void xy::modify( const name            owner,
                 const uint64_t        id,
                 const vector<tag>     tags )
{
    require_auth( owner );
    check( get_id( id ).owner == owner, "owner does not match id");
    check_tags( tags );
    modify_tags( owner, id, tags );
    update_version( id );
}

void xy::modify_tags( const name owner, const uint64_t id, const vector<tag> tags )
{
    auto uid_row = get_id( id );
    name type = uid_row.type;

    if ( type == "node"_n ) {
        auto node_itr = _node.find( id );
        check( node_itr != _node.end(), "node does not exist" );
        consume_modify_tags( owner, node_itr->tags.size(), tags.size() );
        _node.modify( node_itr, get_self(), [&]( auto & row ) {
            row.tags = tags;
        });
    }
    else if ( type == "way"_n ) {
        auto way_itr = _way.find( id );
        check( way_itr != _way.end(), "way does not exist" );
        consume_modify_tags( owner, way_itr->tags.size(), tags.size() );
        _way.modify( way_itr, get_self(), [&]( auto & row ) {
            row.tags = tags;
        });
    }
    else if ( type == "relation"_n ) {
        auto relation_itr = _relation.find( id );
        check( relation_itr != _relation.end(), "relation does not exist" );
        consume_modify_tags( owner, relation_itr->tags.size(), tags.size() );
        _relation.modify( relation_itr, get_self(), [&]( auto & row ) {
            row.tags = tags;
        });
    }
}

void xy::check_tags( const vector<tag> tags )
{
    check( tags.size() <= 255, "[tags] cannot have more than 255 elements");

    std::set<name> duplicates{};
    for ( auto const tag : tags ) {
        check(duplicates.insert(tag.k).second, "[tag.k] all key names must be unique");
        check_tag( tag );
    }
}

void xy::check_tag( const tag tag )
{
    check( tag.k.length() > 0, "[tag.k] must contain at least 1 character");
    check( tag.v.length() <= 255, "[tag.v] cannot be greater than 255 characters");
}
